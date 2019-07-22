// ksvc_securedkeymanagersession.h                                    -*-c++-*-
#ifndef INCLUDED_KSVC_SECUREDKEYMANAGERSESSION
#define INCLUDED_KSVC_SECUREDKEYMANAGERSESSION

#include <ksvc_keymanager.h>

#include <ksvc_keyring.pb.h>
#include <ksvc_cryptokey.pb.h>

namespace MvdS {
namespace ksvc {

// Forward declaration.
class SecurityContext;
  
// ===============================
// Class: SecuredKeyManagerSession
// ===============================

class SecuredKeyManagerSession : public KeyManager
{
  // Provides a secured key manager session through which the key manager can be
  // access in a secure manner. Note that objects of this class will provide a
  // layer that does all necessary security checking.

  // TYPES

  // DATA
  const SecurityContext &d_securityContext;
  KeyManager *           d_keyManager;

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  SecuredKeyManagerSession(const SecurityContext &securityContext,
                           KeyManager *           keyManager);
  // Create secured key manager session using the specified 'securityContext'
  // and the specified 'keyManager'.

  // MANIPULATORS
  void createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                     std::string                              parent,
                     std::string                              keyRingId,
                     KeyRing                                  keyRing);
  // Create a new key ring inside the specified 'parent', with the specified
  // 'keyRingId' using the specified 'keyRing' for initial values.  Is
  // guarranteed to call the specified 'result' at some point in the
  // near future.

  void createCryptoKey(ResultFunction<std::shared_ptr<CryptoKey>> result,
                       std::string                                parent,
                       std::string                                cryptoKeyId,
                       CryptoKey                                  cryptoKey,
                       bool skipInitialVersionCreation = false);
  // Create crypto key inside the specified 'parent'. that has the specified
  // 'cryptoKeyId' and uses the specified 'cryptoKey' for initial values. Is
  // guarranteed to call the specified 'result' at spme point in the near
  // future.    

  // ACCESSORS
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_SECUREDKEYMANAGERSESSION

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
