// a_ksrvs_grpcservice.cpp                                            -*-c++-*-
#include <a_ksrvs_grpcservice.h>

namespace MvdS {
namespace a_ksrvs {

namespace {

void queueWorker(grpc::ServerCompletionQueue *cq)
{
  void *tag = nullptr;
  bool  ok  = false;

  while (d_cq->Next(&tag, &ok)) {
    if (!ok || nullptr == tag) {
      continue;
    }

    (*static_cast<Handler *>(tag))();
  }
}

int convertStatus(const ksvc::ResultStatus &status)
{
  switch (status) {
  case ResultStatus::e_success:
    return grpc::Status::OK;
  case ResultStatus::e_notFound:
    return grpc::Status::NOT_FOUND;
  case ResultStatus::e_timedOut:
    return grpc::Status::DEADLINE_EXCEEDED;
  case ResultStatus::e_exists:
    return grpc::Status::ALREADY_EXISTS;
  case ResultStatus::e_denied:
    return grpc::Status::PERMISSION_DENIED;
  case ResultStatus::e_resourceExhasusted:
    return grps::Status::RESOURCE_EXHAUSTED;
  };

  return grpc::Status::UNKNOWN;
}

template <class Request, class Reply>
using RequestMethod =
    void (AsyncService::*)(grpc::ServerContext *,
                           Request *,
                           grpc::ServerAsyncResponseWriter<Reply> *,
                           grpc::CompletionQueue *,
                           grpc::ServerCompletionQueue *,
                           void *tag);

// ===================
// Class DeleteHandler
// ===================

template <class T>
class DeleteHandler : public GrpcService_QueueHandler
{
  // Provides a handler that just deletes a specific object.

  // DATA
  T *d_object;
  // Allocator *d_allocator;

public:
  // CREATORS
  DeleteHandler(T *object)
      : d_object(object)
  {}

  ~DeleteHandler()
  {
    // Warn/assert when d_Object != nullptr?
  }

  // MANIPULATORS
  virtual void operator()()
  {
    // assert(nullptr != d_object);
    T *object = nullptr;
    std::swap(d_object, object);
    delete object;
  }
};
  
// ====================
// Class RequestContext
// ====================

template <class Request, class Reply>
class RequestContext
{
  friend struct RequestUtil;

  // TYPES
  typedef grpc::ServerAsyncResponseWriter<Reply> Responder;

  // DATA
  grpc::ServerContext                           d_context;
  Request                                       d_request;
  Responder                                     d_responder;
  DeleteHandler<RequestContext<Request, Reply>> d_deleteHandler;
  // Takes care of deleting this object when the response has finished sending.

  // ObjectPool<RequestContext> *d_pool; (allocator?)

  // PRIVATE MANIPULATORS
  void finish(const Reply &reply, const grpc::Status &status)
  // Finish responding by sending the specified 'reply' and using the specified
  // 'status'. When the response has been send, this object will be deleted.
  {
    d_responder.Finish(reply, status, &d_deleteHandler);
  }

  void finishWithError(const grpc::Status &errorStatus)
  // Finish responding by sending the specified 'errorStatus'. When the
  // response has been send, this object will be deleted.
  {
    d_responder.FinishWithError(grpc::Status::OK, &d_deleteHandler);
  }

public:
  // CREATORS
  RequestContext()
      : d_responder(&d_context)
      , d_deleteHandler(this /*, allocator*/)
  {}

};

// ==================
// Struct RequestUtil
// ==================

struct RequestUtil {

  // MANIPULATORS
  template <class Request, class Reply>
  static void finish(std::unique_ptr<RequestContext<Request, Reply>> context,
                     const Reply& reply, const grpc::Status& status)
  // Finish responding by sending the specified 'reply' and using the specified
  // 'status'. When the response has been send, this object will be deleted.
  {
    context.release()->finish(reply, status);
  }

  template <class Request, class Reply>
  static void finishWithError(
      std::unique_ptr<RequestContext<Request, Reply>> context,
      const grpc::Status& status)
  // Finish responding by sending the specified 'errorStatus'. When the
  // response has been send, this object will be deleted.
  {
    context.release()->finishWithError(status);
  }  
};

  
// ====================
// Class RequestHandler
// ====================

template <class Request, class Reply>
class RequestHandler : public GrpcService_QueueHandler
{
  // Provide a request handler for gRPC service RPCs.

public:
  // PUBLIC TYPES
  typedef grpc::ServerAsyncResponseWriter<Reply> Responder;
  typedef std::function<void(
      grpc::ServerContext *, Request *, Responder *, void *)>
      MessageRequest;

private:

  // DATA
  MessageRequest                                  d_messageRequest;
  std::unique_ptr<RequestContext<Request, Reply>> d_requestContext;
  ksvc::RequestHandler                            d_requestHandler;

  // PRIVATE MANIPULATORS
  void registerHandler()
  {
    // TODO: add pool allocator.
    d_requestContext = std::make_unique<RequestContext<Request, Reply>>();
    // TODO: make d_messageRequest() return the context?
    d_messageRequest(&d_requestContext->d_context,
                     &d_requestContext->d_request,
                     &d_requestContext->d_responder,
                     this);
  }

  static void
  handleResponse(std::unique_ptr<RequestContext<Request, Reply>> context,
                 const ResultStatus &                            status,
                 std::shared_ptr<Reply>                          reply)
  {
    if (!status.isSuccess()) {
      RequestUtil::finishWithError(std::move(context), toGrpcStatus(status));
      return;
    }

    RequestUtil::finish(std::move(context), *reply, grpc::Status::OK);
  }

public:
  // CREATORS
  RequestHandler(const MessageRequest &messageRequest,
                 ksvc::RequestHandler *requestHandler)
      : d_messageRequest(messageRequest)
      , d_requestHandler(requestHandler)
  {
    registerHandler();
  }

  // MANIPULATORS
  void operator()() override
  {
    auto context = std::move(d_requestContext); // make this object reentrant.
    registerHandler();                          // reuse handler

    auto responseHandler = std::bind(
        &RequestHandler::handleResponse, this, std::move(context), _1, _2);

    (*d_requestHandler)(std::move(responseHandler), context.d_request);
  }
};

// template <class Request, class Reply>
// void handleCreateKeyRing(
//     std::unique_ptr<RequestContext<Request, Reply>> context)
// {
// }

} // anonymous namespace

// ------------------
// Class: GrpcService
// ------------------

// PRIVATE MANIPULATORS
bool GrpcService::startServer()
{
  grpc::ServerBuilder builder;

  for (const auto &l : d_config.listen) {
    builder.AddListeningPort(l.address(), grpc::InsecureServerCredentials());
  }
  
  builder.RegisterService(&d_service);
  
  d_cq     = builder.AddCompletionQueue();
  d_server = builder.BuildAndStart();
}

bool GrpcService::startWorkers()
{
  d_threads.reserve(d_config.threadCount());
  for (size_t i = 0; i < d_config.threadCount(); ++i) {
    d_threads.emplace_back(&queueWorker, d_cq.get());
  }
}

void GrpcService::registerHandlers()
{
  registerRequestHandler(&AsyncService::RequestCreateKeyRing);
}

void GrpcService::stopQueue()
{
  d_cq->Shutdown();
}
  
void GrpcService::stopWorkers()
{
  for (std::thread &thread : d_threads) {
    thread.join();
  }
  d_threads.clear();
}

template <class Request, class Reply, class Callback>
void GrpcService::registerRequestHandler(RequestMethod<Request, Reply> method)
{
  using namespace std::placeholders;
  auto handler = new RequestHandler<Request, Reply>(
      std::bind(method, d_service, _1, _2, _3, d_cq, d_cq, _4), d_requestHandler);
  ;
  d_handlers.emplace_back(handler);  
}

// CREATORS
GrpcService::GrpcService(ksvc::SecurityManager *    securityManager,
                         const ksvc::ServiceConfig &config)
    : d_config(config)
    , d_securityManager(securityManager)
{}

GrpcService::~GrpcService() {}

// MANIPULATORS
void GrpcService::start()
{
  if (!startServer()) {
    return;
  }

  startWorkers();  
}

void GrpcService::stop()
{
  stopQueue();
  stopWorkers();
}

// MANIPULATORS

// ACCESSORS

} // namespace a_ksrvs
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
