// ksvc_keymanager.cpp                                                -*-c++-*-
#include <ksvc_keymanager.h>

namespace MvdS {
namespace ksvc {

namespace {

class KeyManagerImpl : public KeyManager
{

  // TYPES

  // DATA
  KeyStore *d_keyStore;
  Crypto *  d_crypto;

  // PRIVATE MANIPULATORS
  
public:
  // CREATORS
  KeyManageImpl(KeyStore *keyStore, Crypto *crypto, const Configuration &config)
    : d_keyStore(keyStore)
    , d_crypto(crypto)
  {
  }
  
  // MANIPULATORS
  void
  KeyManager::createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                            std::string                              parent,
                            std::string                              keyRingId,
                            KeyRing                                  keyRing)
  {
    d_keyStore->createKeyRing(std::move(result),
                              std::move(parent),
                              std::move(keyRingId),
                              std::move(keyRing));
  }

  void
  KeyManager::createCryptoKey(ResultFunction<std::shared_ptr<CryptoKey>> result,
                              std::string                                parent,
                              std::string cryptoKeyId,
                              CryptoKey   cryptoKey,
                              bool        skipInitialVersionCreation = false)
  {
    std::shared_ptr<CryptoKeyVersion> version;
    
    if (!skipInitialVersionCreation) {
      version = d_crypto->createCryptoKey(cryptoKey);
    }    

    d_keyStore->createCryptoKey(std::move(result),
				std::move(parent),
				std::move(cryptoKeyId),
				std::move(cryptoKey),
				std::move(version));
  }

  // ACCESSORS
  };

}

// -----------------
// Class: KeyManager
// -----------------

// CREATORS
KeyManager *
KeyManager::create(KeyStore *keyStore, Crypto *crypto, const Configuration &config)
{
}

// MANIPULATORS

// ACCESSORS

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
