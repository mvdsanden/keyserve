// ksvc_cachingkeystore.h                                             -*-c++-*-
#ifndef INCLUDED_KSVC_CACHINGKEYSTORE
#define INCLUDED_KSVC_CACHINGKEYSTORE

#include <ksvc_keystore.h>

#include <shared_mutex>
#include <memory>

namespace MvdS {
namespace ksvc {

// ======================
// Class: CachingKeyStore
// ======================

class CachingKeyStore : public KeyStore
{
  // Provides a caching key store.

  // TYPES
  template <class T>
  struct CacheType
  {
    // TYPES
    using TypeSP = std::shared_ptr<T>;

    // DATA
    std::mutex                        d_mutex;
    TypeSP                            d_object;
    std::list<ResultFunction<TypeSP>> d_waitList;

    // MANIPULATORS
    void getValue(ResultFunction<std::shared_ptr<T>> result);
    // Calls the specified 'result' some time in the future with the cached
    // value. Note that the value might not yet be available, in which case it
    // will wait for the backend to provide it. The result could also be called
    // with an 'e_timedout' status.
  };

  typedef std::variant<CacheType<KeyRing>, CacheType<CryptoKey>> CacheObject;
  
  typedef std::unordered_map<std::string, std::shared_ptr<CacheObject>>
      CacheMap;

  // DATA
  std::shared_mutex d_mutex;
  CacheMap          d_cache;

  // PRIVATE MANIPULATORS
  std::shared_ptr<CacheObject> getCacheObject(const std::string& name);
  // Return object wthh the specified 'name' if it exists in the cache, return
  // 'nullptr' otherwise.

  template <class T>
  std::shared_ptr<CacheObject> createCacheObject(const std::string &name,
                                                 bool *             created);
  // If an object with the specified 'name' does not exist in the cache yet,
  // created it and return the new object and set the specified 'created' to
  // true. Otherwise return the existing object.

  template <class T>
  std::shared_ptr<CacheObject>
  getCacheValue(ResultFunction<std::shared_ptr<T>> result, std::string name);
  // Call the specified 'result' for the cache value with the specified 'name'.
  // Return corresponding cache object if an empty cache value was created.

  template <class T>
  void updateCacheValue(const ResultStatus& status, std::shared_ptr<T> value);
  
public:
  // CREATORS
  CachingKeyStore(KeyStore *backingKeyStore);
  // Create a caching key store with the specified 'backingKeyStore'.

  ~CachingKeyStore();
  
  // MANIPULATORS
  void createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                     std::string                              parent,
                     std::string                              keyRingId,
                     KeyRing                                  keyRing) override;
  // Create key ring with the specified 'parent', the specified 'keyRingId',
  // using the specified 'keyRing' for initial values. Call the specified
  // 'result' with the created ring or with the 'e_duplicateId' status code.

  void createCryptoKey(
      ResultFunction<std::shared_ptr<CryptoKey>> result,
      std::string                                parent,
      std::string                                cryptoKeyId,
      CryptoKey                                  cryptoKey,
      std::shared_ptr<CryptoKeyVersion> cryptoKeyVersion = nullptr) override;
  // Create crypto key with the specified 'parent', the specified 'cryptoKeyId',
  // using the specified 'cryptoKey' for initial values and optionally adds the
  // specified 'cryptoKeyVersion' as initial version. Call the specified
  // 'result' with the created key or with the 'e_duplicateId' status code.

  void getKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                  std::string                              name) const override;
  // Get key ring with the specified 'name'. Call the specified 'result' with
  // the key ring or with the 'e_notFound' status code.

  void getCryptoKey(ResultFunction<std::shared_ptr<KeyRing>> result,
                    std::string name) const override;
  // Get crypto key with the specified 'name'. Call the specified 'result' with
  // the crypto key or with the 'e_notFound' status code.
};

// ----------------------------------
// Class CachingKeyStore::CacheObject
// ----------------------------------

template <class T>
void CachingKeyStore::CacheObject::getValue(
    ResultFunction<std::shared_ptr<T>> result)
{
  auto guard = std::unique_lock(d_mutex);
  if (d_object) {
    result(ResultStatus::e_success, d_object);
    return;
  }

  d_waitList.emplace_back(std::move(result));
}

// ---------------------
// Class CachingKeyStore
// ---------------------

template <class T>
std::shared_ptr<CacheObject> CachingKeyStore::createCacheObject(const std::string &name, bool *created)
{
  auto guard = std::unique_lock(d_mutex);
  auto [iter, res] = d_cache.emplace(name, CacheType<T>());
  *created = res;
  return iter->second;
}

template <class T>
std::shared_ptr<CacheObject> CachingKeyStore::getCacheValue(
    ResultFunction<std::shared_ptr<T>> result, std::string name)
{
  bool created = false;
  std::shared_ptr<CacheObject> object = std::move(getCacheObject(name));

  if (!object) {
    object = std::move(createCacheObject<T>(name, &created));
  }

  if (!holds_alternative<CacheType<T>>(*object)) {
    result(ResultStatus::e_notFound, nullptr);
    return;
  }

  std::get<CacheType<T>>(*object).getValue(result);

  return created ? std::move(object) : nullptr;
}

template <class T>
void CachingKeyStore::updateCacheValue(const ResultStatus &status, std::shared_ptr<T> value)
{

  
  
}

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_CACHINGKEYSTORE

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
