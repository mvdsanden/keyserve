// ksvc_cachingkeystore.cpp                                           -*-c++-*-
#include <ksvc_cachingkeystore.h>
#include <ksvc_cryptokey.pb.h>
#include <ksvc_keyring.pb.h>

namespace MvdS {
namespace ksvc {
  
// ----------------------
// Class: CachingKeyStore
// ----------------------

std::shared_ptr<CachingKeyStore::CacheObject>
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
    KeyRing                                  keyRing)
{
  using namespace std::placeholders;
  
  std::string name;
  name.reserve(parent.size() + keyRingId.size() + 1);
  name += parent;
  name += "/";
  name += keyRingId;

  std::shared_ptr<CacheObject> cacheObject = std::move(createCacheValue(result, name));
  if (!cacheObject) {
    result(ResultStatus::e_exists, nullptr);
    return;
  }

  d_backingKeyStore->createKeyRing(
      std::bind(&CachingKeyStore::updateCacheValue<KeyRing>,
                this,
                _1,
                _2,
                std::move(cacheObject)),
      std::move(parent),
      std::move(keyRingId),
      std::move(keyRing));
}

void CachingKeyStore::createCryptoKey(
    ResultFunction<std::shared_ptr<CryptoKey>> result,
    std::string                                parent,
    std::string                                cryptoKeyId,
    CryptoKey                                  cryptoKey,
    std::shared_ptr<CryptoKeyVersion>          cryptoKeyVersion)
{
  using namespace std::placeholders;
  
  std::string name;
  name.reserve(parent.size() + cryptoKeyId.size() + 1);
  name += parent;
  name += "/";
  name += cryptoKeyId;

  std::shared_ptr<CacheObject> cacheObject = std::move(createCacheValue(result, name));
  if (!cacheObject) {
    result(ResultStatus::e_exists, nullptr);
    return;
  }

  d_backingKeyStore->createCryptoKey(
      std::bind(&CachingKeyStore::updateCacheValue<CryptoKey>,
                this,
                _1,
                _2,
                std::move(cacheObject)),
      std::move(parent),
      std::move(cryptoKeyId),
      std::move(cryptoKey));
}

void CachingKeyStore::getKeyRing(
    ResultFunction<std::shared_ptr<KeyRing>> result, std::string name)
{
  using namespace std::placeholders;
  
  std::shared_ptr<CacheObject> cacheObject = std::move(getCacheValue(result, name));
  if (!cacheObject) {
    // Cache object was not newly created, which means 'result' was already
    // called.
    return;
  }

  // The 'result' was added to the wait list of the cache object, so when the
  // backing store updates the cache value 'result' will be called.
  d_backingKeyStore->getKeyRing(
      std::bind(&CachingKeyStore::updateCacheValue<KeyRing>,
                this,
                _1,
                _2,
                std::move(cacheObject)),
      std::move(name));
}

void CachingKeyStore::getCryptoKey(
    ResultFunction<std::shared_ptr<CryptoKey>> result, std::string name)
{
  using namespace std::placeholders;

  std::shared_ptr<CacheObject> cacheObject = std::move(getCacheValue(result, name));
  if (!cacheObject) {
    // Cache object was not newly created, which means 'result' was already
    // called.
    return;
  }

  // The 'result' was added to the wait list of the cache object, so when the
  // backing store updates the cache value 'result' will be called.
  d_backingKeyStore->getCryptoKey(
      std::bind(&CachingKeyStore::updateCacheValue<CryptoKey>,
                this,
                _1,
                _2,
                std::move(cacheObject)),
      std::move(name));
}

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
