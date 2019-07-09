// ksvc_securedkeymanagersession.h                                    -*-c++-*-
#ifndef INCLUDED_KSVC_SECUREDKEYMANAGERSESSION
#define INCLUDED_KSVC_SECUREDKEYMANAGERSESSION

namespace MvdS {
namespace ksvc {

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
  bool validateCreateKeyRing(const std::string &parent,
                             const std::string &keyRingId,
                             const KeyRing &    keyRing);

  bool validateCreateCryptoKey(const std::string &parent,
                               const std::string &cryptoKeyId,
                               const CryptoKey &  cryptoKey,
                               bool               skipInitialVersionCreation);

public:
  // CREATORS
  SecuredKeyManagerSession(const SecurityContext &securityContext,
                           KeyManager *           keyManager);
  // ...

  // MANIPULATORS
  void createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                     std::string                              parent,
                     std::string                              keyRingId,
                     KeyRing                                  keyRing)
  // Create a new key ring inside the specified 'parent', with the specified
  // 'keyRingId' using the specified 'keyRing' for initial values.  Is
  // guarranteed to call the specified 'result' at some point in the
  // near future.
  {
    if (!validateCreateKeyRing(parent, keyRingId, keyRing)) {
      result(ResultStatus::e_denied, nullptr);
      return;
    }

    d_keyManager->createKeyRing(std::move(result),
                                std::move(parent),
                                std::move(keyRingId),
                                std::move(keyRing));
  }

  void createCryptoKey(ResultFunction<std::shared_ptr<CryptoKey>> result,
                       std::string                                parent,
                       std::string                                cryptoKeyId,
                       CryptoKey                                  cryptoKey,
                       bool skipInitialVersionCreation = false)
  // Create crypto key inside the specified 'parent'. that has the specified
  // 'cryptoKeyId' and uses the specified 'cryptoKey' for initial values. Is
  // guarranteed to call the specified 'result' at spme point in the near
  // future.    
  {
    if (!validateCreateCryptoKey(
            parent, cryptoKeyId, cryptoKey, skipInitialVersionCreation)) {
      result(ResultStates::e_denied, nullptr);
      return;
    }

    d_keyManager->createCryptoKey(std::move(parent),
                                  std::move(cryptoKeyId),
                                  std::move(cryptoKey),
                                  skipInitialVersionCreation);
  }

  // ACCESSORS
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_SECUREDKEYMANAGERSESSION

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
