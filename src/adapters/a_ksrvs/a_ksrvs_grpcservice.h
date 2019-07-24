// a_ksrvs_grpcservice.h                                              -*-c++-*-
#ifndef INCLUDED_A_KSRVS_GRPCSERVICE
#define INCLUDED_A_KSRVS_GRPCSERVICE

#include <ksvc_service.h>

#include <vector>
#include <thread>

namespace MvdS {

// Forward declarations.
namespace ksvc {
class SecurityManager;
class Configuration;
class ServiceConfig;
}

namespace a_ksrvs {

// ===============================
// Class: GrpcService_QueueHandler
// ===============================

class GrpcService_QueueHandler
{
public:
  virtual void operator()() = 0;
};
  
// ==================
// Class: GrpcService
// ==================

class GrpcService : public ksvc::Service
{
  // ...

  // TYPES
  typedef ksvc::KeyServeService::AsyncService                    AsyncService;
  typedef std::vector<std::unique_ptr<GrpcService_QueueHandler>> Handler;
  template <class Request, class Reply>
  using RequestMethod = void (ksvc::KeyServeService::AsyncService::*)(
      grpc::ServerContext *,
      Request *,
      grpc::ServerAsyncResponseWriter<Reply> *,
      grpc::CompletionQueue *,
      grpc::ServerCompletionQueue *,
      void *tag);

  // DATA
  ksvc::ServiceConfig                          d_config;
  ksvc::SecurityManager *                      d_securityManager;
  std::vector<std::thread>                     d_threads;
  AsyncService                                 d_service;
  std::unique_ptr<grpc::ServerCompletionQueue> d_cq;
  std::unique_ptr<grpc::Server>                d_server;
  Handlers                                     d_handler;

  // PRIVATE MANIPULATORS
  bool startServer();
  bool startWorkers();
  void registerHandlers();
  void stopQueue();
  void stopWorkers();

  template <class Request, class Reply, class Callback>
  void registerRequestHandler(RequestMethod<Request, Reply> method,
                              Callback                      callback);

public:
  // CREATORS
  GrpcService(ksvc::SecurityManager *    securityManager,
              const ksvc::ServiceConfig &config);
  // Create gRPC service using the specified 'securityManager' and the specified
  // 'config'.

  ~GrpcService();

  // MANIPULATORS
  void start() override;
  // Start asynchornous service.

  void stop() override;
  // Stop asynchronous service.

  // ACCESSORS
};

} // namespace a_ksrvs
} // namespace MvdS

#endif // INCLUDED_A_KSRVS_GRPCSERVICE

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
