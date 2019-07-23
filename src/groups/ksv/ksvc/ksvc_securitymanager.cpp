// ksvc_securitymanager.cpp                                           -*-c++-*-
#include <ksvc_securedkeymanager.h>
#include <ksvc_securedkeymanagersession.h>
#include <ksvc_securitycontext.h>
#include <ksvc_securitycredentials.h>
#include <ksvc_securitymanager.h>
#include <ksvc_keymanager.h>

namespace MvdS {
namespace ksvc {

namespace {

class DummySecurityContext : public SecurityContext
{
public:
  // CREATORS

  // MANIPULATORS

  // ACCESSORS
  void validateParent(std::function<void(bool)> result,
                      std::string               parent) const override
  // Validate the specified 'parent'. The specified 'result' callback is
  // called sometime in the near future with the validation result.
  {
    result(true);
  }
};

} // namespace

// ----------------------
// Class: SecurityManager
// ----------------------

// PRIVATE MANIPULATORS
void SecurityManager::logon(
    ResultFunction<std::shared_ptr<SecurityContext>> result,
    std::unique_ptr<SecurityCredentials>             credentials)
{
  // TODO: implement actual security checks.
  result(ResultStatus::e_success, std::make_shared<DummySecurityContext>());
}

void SecurityManager::logonResult(
    ResultFunction<std::shared_ptr<KeyManager>> result,
    const ResultStatus &                        status,
    std::shared_ptr<SecurityContext>            securityContext)
{
  if (!status.isSuccess()) {
    result(status, nullptr);
    return;
  }

  std::shared_ptr<SecuredKeyManagerSession> session(
      d_securedKeyManager->createSession(std::move(securityContext)));

  if (!session) {
    result(ResultStatus::e_denied, nullptr);
    return;
  }

  result(ResultStatus::e_success, session);
}

// CREATORS
SecurityManager::SecurityManager(SecuredKeyManager *securedKeyManager)
    : d_securedKeyManager(securedKeyManager)
{}

// MANIPULATORS
void SecurityManager::createSession(
    ResultFunction<std::shared_ptr<KeyManager>> result,
    std::unique_ptr<SecurityCredentials>        credentials)
{
  using namespace std::placeholders;

  std::function<void(const ResultStatus &, std::shared_ptr<SecurityContext>)>
      call = std::bind(
          &SecurityManager::logonResult, this, std::move(result), _1, _2);

  logon(std::move(call), std::move(credentials));
}

// MANIPULATORS

// ACCESSORS

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
