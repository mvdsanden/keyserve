// ksvc_securedkeymanager.cpp                                         -*-c++-*-
#include <ksvc_securedkeymanager.h>
#include <ksvc_securedkeymanagersession.h>

namespace MvdS {
namespace ksvc {

// ------------------------
// Class: SecuredKeyManager
// ------------------------

// PRIVATE MANIPULATORS
std::unique_ptr<SecuredKeyManagerSession>
SecuredKeyManager::createSession(const SecurityContext &securityContext)
{
  return std::make_unique<SecuredKeyManagerSession>(securityContext,
                                                    d_keyManager);
}

  
// CREATORS
SecuredKeyManager::SecuredKeyManager(KeyManager *         keyManager,
                                     const Configuration &config)
    : d_keyManager(keyManager)
{}

// MANIPULATORS

// ACCESSORS

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
