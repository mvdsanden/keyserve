// ksvc_cachingkeystore.cpp                                           -*-c++-*-
#include <ksvc_cachingkeystore.h>

namespace MvdS {
namespace ksvc {
  
// ----------------------
// Class: CachingKeyStore
// ----------------------

std::shared_ptr<CacheObject>
CachingKeyStore::getCacheObject(const std::string &name)
{
  auto guard = std::shared_lock(d_mutex);
  auto iter = d_cache.find(name);
  return (d_cache.end() == iter)?nullptr:iter->second;
}
  
// CREATORS
CachingKeyStore::CachingKeyStore(KeyStore *backingKeyStore)
    : d_backingKeyStore(backingKeyStore)
{}

CachingKeyStore::~CachingKeyStore() {}

// MANIPULATORS
void CachingKeyStore::createKeyRing(
    ResultFunction<std::shared_ptr<KeyRing>> result,
    std::string                              parent,
    std::string                              keyRingId,
    KeyRing                                  keyRing) override
{
}

void CachingKeyStore::createCryptoKey(
    ResultFunction<std::shared_ptr<CryptoKey>> result,
    std::string                                parent,
    std::string                                cryptoKeyId,
    CryptoKey                                  cryptoKey,
    std::shared_ptr<CryptoKeyVersion> cryptoKeyVersion = nullptr) override
{
}

void CachingKeyStore::getKeyRing(
    ResultFunction<std::shared_ptr<KeyRing>> result,
    std::string                              name) override
{
  std::shared_ptr<CacheObject> cacheObject = getCacheValue(result, name);
  if (!cacheObject) {
    return;
  }

  d_backingKeyStore->getKeyRing(
      std::bind(&CachingKeyStore::updateCacheValue<KeyRing>, this), name);
}

void CachingKeyStore::getCryptoKey(
    ResultFunction<std::shared_ptr<KeyRing>> result,
    std::string                              name) override
{
  std::shared_ptr<CacheObject> cacheObject = getCacheValue(result, name);
  if (!cacheObject) {
    return;
  }

  d_backingKeyStore->getCryptoKey(
      std::bind(&CachingKeyStore::updateCacheValue<CryptoKey>,
                this,
                cacheObject,
                _1,
                _2),
      name);
}

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
