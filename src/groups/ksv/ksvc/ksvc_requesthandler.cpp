// ksvc_requesthandler.cpp                                            -*-c++-*-
#include <ksvc_keymanager.h>
#include <ksvc_requesthandler.h>
#include <ksvc_securitycredentials.h>
#include <ksvc_securitymanager.h>

#include <ksvc_keyserveservice.pb.h>

namespace MvdS {
namespace ksvc {

namespace {

template <class Reply, class Method, class... Args>
void handleSecured(ResultFunction<std::shared_ptr<Reply>> result,
                   const ResultStatus &                   status,
                   std::shared_ptr<KeyManager>            keyManager,
                   Method                                 method,
                   Args... args)
{
  if (!status.isSuccess()) {
    result(ResultStatus::e_denied, nullptr);
    return;
  }

  std::invoke(method, keyManager.get(), std::move(result), std::move(args)...);
}

template <class Reply, class Method, class... Args>
void handle(SecurityManager *                      securityManager,
            ResultFunction<std::shared_ptr<Reply>> result,
            Method                                 method,
            Args... args)
{
  using namespace std::placeholders;
  auto securityCredentials = std::make_unique<SecurityCredentials>();
  auto secureHandler       = std::bind(&handleSecured<Reply, Method, Args...>,
                                 std::move(result),
                                 _1,
                                 _2,
                                 method,
                                 args...);

  securityManager->createSession(std::move(secureHandler),
                                 std::move(securityCredentials));
}

} // anonymous namespace

// ---------------------
// Class: RequestHandler
// ---------------------

// PRIVATE MANIPULATORS
  
// CREATORS
RequestHandler::RequestHandler(SecurityManager *securityManager)
  : d_securityManager(securityManager)
{}

// MANIPULATORS
void RequestHandler::operator()(ResultFunction<std::shared_ptr<KeyRing>> result,
                                const CreateKeyRingRequest &request)
{
  handle(d_securityManager,
         std::move(result),
         &KeyManager::createKeyRing,
         request.parent(),
         request.keyringid(),
         request.keyring());
}

void RequestHandler::
     operator()(ResultFunction<std::shared_ptr<CryptoKey>> result,
           const CreateCryptoKeyRequest &             request)
{
  handle(d_securityManager,
         std::move(result),
         &KeyManager::createCryptoKey,
         request.parent(),
         request.cryptokeyid(),
         request.cryptokey(),
         request.skipinitialversioncreation());
}

// MANIPULATORS

// ACCESSORS

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
