// a_kstor_memorykeystore.h                                           -*-c++-*-
#ifndef INCLUDED_A_KSTOR_MEMORYKEYSTORE
#define INCLUDED_A_KSTOR_MEMORYKEYSTORE

#include <ksvc_keystore.h>

#include <shared_mutex>

namespace MvdS {

// Forward declarations
namespace ksvc {
class KeyStoreConfig;
}
  
namespace a_kstor {

// =====================
// Class: MemoryKeyStore
// =====================

class MemoryKeyStore : public ksvc::KeyStore
{
  // ...

  // TYPES
  template <class T>
  using ObjectMap = std::unordered_map<std::string, std::shared_ptr<T>>;

  typedef ObjectMap<ksvc::KeyRing>   KeyRingMap;
  typedef ObjectMap<ksvc::CryptoKey> CryptoKeyMap;

  // DATA
  KeyRingMap        d_keyRings;
  std::shared_mutex d_keyRingsMutex;
  
  CryptoKeyMap      d_cryptoKeys;
  std::shared_mutex d_cryptoKeysMutex;

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  MemoryKeyStore(const ksvc::KeyStoreConfig &config);
  // Create memory key store using the specified 'config'.

  void
  createKeyRing(ksvc::ResultFunction<std::shared_ptr<ksvc::KeyRing>> result,
                std::string                                          parent,
                std::string                                          keyRingId,
                ksvc::KeyRing keyRing) override;
  // Create key ring with the specified 'parent', the specified 'keyRingId',
  // using the specified 'keyRing' for initial values. Call the specified
  // 'result' with the created ring or with the 'e_duplicateId' status code.

  void
  createCryptoKey(ksvc::ResultFunction<std::shared_ptr<ksvc::CryptoKey>> result,
                  std::string                                            parent,
                  std::string                             cryptoKeyId,
                  ksvc::CryptoKey                         cryptoKey,
                  std::shared_ptr<ksvc::CryptoKeyVersion> cryptoKeyVersion =
                      nullptr) override;
  // Create crypto key with the specified 'parent', the specified 'cryptoKeyId',
  // using the specified 'cryptoKey' for initial values and optionally adds the
  // specified 'cryptoKeyVersion' as initial version. Call the specified
  // 'result' with the created key or with the 'e_duplicateId' status code.

  void getKeyRing(ksvc::ResultFunction<std::shared_ptr<ksvc::KeyRing>> result,
                  std::string name) override;
  // Get key ring with the specified 'name'. Call the specified 'result' with
  // the key ring or with the 'e_notFound' status code.

  void
  getCryptoKey(ksvc::ResultFunction<std::shared_ptr<ksvc::CryptoKey>> result,
               std::string name) override;
  // Get crypto key with the specified 'name'. Call the specified 'result' with
  // the crypto key or with the 'e_notFound' status code.

  // ACCESSORS
};

} // namespace a_kstor
} // namespace MvdS

#endif // INCLUDED_A_KSTOR_MEMORYKEYSTORE

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
