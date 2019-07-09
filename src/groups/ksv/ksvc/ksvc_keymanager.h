// ksvc_keymanager.h                                                  -*-c++-*-
#ifndef INCLUDED_KSVC_KEYMANAGER
#define INCLUDED_KSVC_KEYMANAGER

namespace MvdS {
namespace ksvc {

// =================
// Class: KeyManager
// =================

class KeyManager
{
  // Provide key manager that is responsible for handling all possible requests.
  // Note that this is class is not aware of any security. All security checks
  // are implemented by the SecuredKeyManager, which can be used to created
  // secured key manager sessions that wrap this object.

  // TYPES

  // DATA

  // PRIVATE MANIPULATORS

public:
  // PUBLIC TYPES
  template <class T>
  using ResultFunction = std::function<void (const ResultStatus&, T)>;

  // CREATORS
  static KeyManager *
  create(KeyStore *keyStore, Crypto *crypto, const Configuration &config);
  // Create key manager that uses the specified 'keyStore' and the specified
  // 'crypto', getting specifics out of the specified 'config'.

  // MANIPULATORS
  virtual void createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                             std::string                              parent,
                             std::string                              keyRingId,
                             KeyRing keyRing) = 0;
  // Create key ring inside the specified 'parent', with the specified
  // 'keyRingId' using the specified 'keyRing' for initial values. Is
  // guarranteed to call the specified 'result' at some point in the
  // near future.

  virtual void
  createCryptoKey(ResultFunction<std::shared_ptr<CryptoKey>> result,
                  std::string                                parent,
                  std::string                                cryptoKeyId,
                  CryptoKey                                  cryptoKey,
                  bool skipInitialVersionCreation = false) = 0;
  // Create crypto key inside the specified 'parent'. that has the specified
  // 'cryptoKeyId' and uses the specified 'cryptoKey' for initial values. Is
  // guarranteed to call the specified 'result' at spme point in the near
  // future.

  // ACCESSORS
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_KEYMANAGER

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
