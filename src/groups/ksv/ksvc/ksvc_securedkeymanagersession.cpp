// ksvc_securedkeymanagersession.cpp                                  -*-c++-*-
#include <ksvc_securedkeymanagersession.h>

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
}; // anonymous namespace

// -------------------------------
// Class: SecuredKeyManagerSession
// -------------------------------

  // PRIVATE MANIPULATORS
bool SecuredKeyManagerSession::validateCreateKeyRing(
    const std::string &parent,
    const std::string &keyRingId,
    const KeyRing &    keyRing)
{
  if (!checkIdSyntax(keyRingId)) {
    return false;
  }
  return true;
}

bool SecuredKeyManagerSession::validateCreateCryptoKey(
    const std::string &parent,
    const std::string &cryptoKeyId,
    const CryptoKey &  cryptoKey,
    bool               skipInitialVersionCreation)
{
  if (!checkIdSyntax(cryptoKeyId)) {
    return false;
  }
  return true;
}
  
// CREATORS
SecuredKeyManagerSession::SecuredKeyManagerSession(
    const SecurityContext &securityContext, KeyManager *keyManager)
    : d_securityContext(securityContext)
    , d_keyManager(keyManager)
{}

// MANIPULATORS

// ACCESSORS

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
