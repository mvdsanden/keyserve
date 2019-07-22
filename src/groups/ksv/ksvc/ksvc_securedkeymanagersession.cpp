// ksvc_securedkeymanagersession.cpp                                  -*-c++-*-
#include <ksvc_securedkeymanagersession.h>

#include <ksvc_securitycontext.h>

namespace MvdS {
namespace ksvc {

namespace {
bool checkIdSyntax(const std::string &id)
{
  if (id.find('/') != std::string::npos) {
    return false;
  }
  return true;  
}

template <class T>
using InternalCall = std::function<void(T)>;

template <class T>
using PipelineCall = InternalCall<ResultFunction<std::shared_ptr<T>>>;

template <class ResultType, class CallType>
void validationPipeline(ResultType result, CallType call, bool status = true)
{
  if (!status) {
    result(ResultStatus::e_denied, nullptr);
    return;
  }

  call(std::move(result));
}

template <class ResultType,
          class CallType,
          class Validator,
          class... Validators>
void validationPipeline(ResultType result,
              CallType   call,
              Validator  validator,
              Validators... remaining,
              bool status = true)
// Asynchronous validator calling pipeline. Call the specified 'validator' with
// a recursive result callback on the specified 'remaining' validators. If one
// of the validators fails, call the specifies 'result' with 'e_denied'. If all
// validators succeed, call the specified 'call' with 'result'. Note that this
// passes 'result' using move semantics, which means there is no need to copy
// it.
{
  using namespace std::placeholders;
  
  if (!status) {
    result(ResultStatus::e_denied, nullptr);
    return;
  }

  validator(std::bind(&validationPipeline<ResultType, CallType, Validators...>,
                      std::move(result),
                      std::move(call),
                      std::move(remaining)...,
                      _1));
}

}; // anonymous namespace

// -------------------------------
// Class: SecuredKeyManagerSession
// -------------------------------

// PRIVATE MANIPULATORS

// CREATORS
SecuredKeyManagerSession::SecuredKeyManagerSession(
    const SecurityContext &securityContext, KeyManager *keyManager)
    : d_securityContext(securityContext)
    , d_keyManager(keyManager)
{}

// MANIPULATORS
void SecuredKeyManagerSession::createKeyRing(
    ResultFunction<std::shared_ptr<KeyRing>> result,
    std::string                              parent,
    std::string                              keyRingId,
    KeyRing                                  keyRing)
{
  using namespace std::placeholders;

  if (!checkIdSyntax(keyRingId)) {
    result(ResultStatus::e_denied, nullptr);
    return;
  }

  PipelineCall<KeyRing> call = std::bind(&KeyManager::createKeyRing,
                                         d_keyManager,
                                         _1,
                                         std::move(parent),
                                         std::move(keyRingId),
                                         std::move(keyRing));

  validationPipeline(
      std::move(result),
      std::move(call),
      std::bind(
          &SecurityContext::validateParent, &d_securityContext, _1, parent));
}

void SecuredKeyManagerSession::createCryptoKey(
    ResultFunction<std::shared_ptr<CryptoKey>> result,
    std::string                                parent,
    std::string                                cryptoKeyId,
    CryptoKey                                  cryptoKey,
    bool                                       skipInitialVersionCreation)
{
  using namespace std::placeholders;

  if (!checkIdSyntax(cryptoKeyId)) {
    result(ResultStatus::e_denied, nullptr);
    return;
  }

  PipelineCall<CryptoKey> call = std::bind(&KeyManager::createCryptoKey,
                                           d_keyManager,
                                           _1,
                                           std::move(parent),
                                           std::move(cryptoKeyId),
                                           std::move(cryptoKey),
                                           skipInitialVersionCreation);

  validationPipeline(
      std::move(result),
      std::move(call),
      std::bind(
          &SecurityContext::validateParent, &d_securityContext, _1, parent));
}

// ACCESSORS

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
