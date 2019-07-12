// ksvc_keystore.h                                                    -*-c++-*-
#ifndef INCLUDED_KSVC_KEYSTORE
#define INCLUDED_KSVC_KEYSTORE

#include <ksvc_resultfunction.h>

#include <string>
#include <memory>

namespace MvdS {
namespace ksvc {

// Forward declarations
class KeyRing;
class CryptoKey;
  
// ===============
// Class: KeyStore
// ===============

class KeyStore
{
  // Provides an abstract interface for the keyStore.

public:
  // MANIPULATORS
  virtual void createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                             std::string                              parent,
                             std::string                              keyRingId,
                             KeyRing keyRing) = 0;
  // Create key ring with the specified 'parent', the specified 'keyRingId',
  // using the specified 'keyRing' for initial values. Call the specified
  // 'result' with the created ring or with the 'e_duplicateId' status code.

  virtual void createCryptoKey(
      ResultFunction<std::shared_ptr<CryptoKey>> result,
      std::string                                parent,
      std::string                                cryptoKeyId,
      CryptoKey                                  cryptoKey,
      std::shared_ptr<CryptoKeyVersion> cryptoKeyVersion = nullptr) = 0;
  // Create crypto key with the specified 'parent', the specified 'cryptoKeyId',
  // using the specified 'cryptoKey' for initial values and optionally adds the
  // specified 'cryptoKeyVersion' as initial version. Call the specified
  // 'result' with the created key or with the 'e_duplicateId' status code.

  virtual void getKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                          std::string name) = 0;
  // Get key ring with the specified 'name'. Call the specified 'result' with
  // the key ring or with the 'e_notFound' status code.

  virtual void getCryptoKey(ResultFunction<std::shared_ptr<KeyRing>> result,
                            std::string name)  = 0;
  // Get crypto key with the specified 'name'. Call the specified 'result' with
  // the crypto key or with the 'e_notFound' status code.
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_KEYSTORE

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
