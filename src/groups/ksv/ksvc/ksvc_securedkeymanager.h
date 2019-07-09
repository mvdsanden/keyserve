// ksvc_securedkeymanager.h                                           -*-c++-*-
#ifndef INCLUDED_KSVC_SECUREDKEYMANAGER
#define INCLUDED_KSVC_SECUREDKEYMANAGER

namespace MvdS {
namespace ksvc {

// ========================
// Class: SecuredKeyManager
// ========================

class SecuredKeyManager
{
  // Provides a secured key manager. It can be used (only) by the security
  // manager to created secured key manager sessions.

  friend class SecurityManager;
  
  // TYPES

  // DATA
  KeyManager *d_manager;

  // PRIVATE MANIPULATORS
  std::unique_ptr<SecuredKeyManagerSession>
  createSession(const SecurityContext &securityContext);

public:
  // CREATORS
  SecuredKeyManager(KeyManager *keyManager, const Configuration &config);
  // Create secured key manager that layers ontop of the specified 'keyManager'
  // using the specified 'config'.

  // MANIPULATORS

  // ACCESSORS
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_SECUREDKEYMANAGER

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
