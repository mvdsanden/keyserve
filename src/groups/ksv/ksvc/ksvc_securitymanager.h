// ksvc_securitymanager.h                                             -*-c++-*-
#ifndef INCLUDED_KSVC_SECURITYMANAGER
#define INCLUDED_KSVC_SECURITYMANAGER

#include <ksvc_resultfunction.h>

#include <memory>

namespace MvdS {
namespace ksvc {

// Forward declarations.
class SecuredKeyManager;
class KeyManager;
class SecurityCredentials;
class SecurityContext;

// ======================
// Class: SecurityManager
// ======================

class SecurityManager
{
  // ...

  // TYPES

  // DATA
  SecuredKeyManager *d_securedKeyManager;

  // PRIVATE MANIPULATORS
  void logon(ResultFunction<std::shared_ptr<SecurityContext>> result,
             std::unique_ptr<SecurityCredentials>             credentials);

  void logonResult(ResultFunction<std::shared_ptr<KeyManager>> result,
                   const ResultStatus &                        status,
                   std::shared_ptr<SecurityContext>            securityContext);

public:
  // CREATORS
  SecurityManager(SecuredKeyManager *securedKeyManager);
  // Create security manager that uses the specified 'securedKeyManager'.

  // MANIPULATORS
  void createSession(ResultFunction<std::shared_ptr<KeyManager>> result,
                     std::unique_ptr<SecurityCredentials>        credentials);
  // Create a session using the specified 'credentials'. This will call the
  // specified 'result' in the near future. It can result in 'e_success' in
  // which case the result will contain the sessions key manager or it can
  // result in 'e_denied'.

  // ACCESSORS
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_SECURITYMANAGER

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
