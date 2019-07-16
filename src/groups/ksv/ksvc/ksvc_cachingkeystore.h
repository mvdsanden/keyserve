// ksvc_cachingkeystore.h                                             -*-c++-*-
#ifndef INCLUDED_KSVC_CACHINGKEYSTORE
#define INCLUDED_KSVC_CACHINGKEYSTORE

#include <ksvc_keystore.h>
#include <ksvc_resultfunction.h>

#include <ksvc_cryptokey.pb.h>
#include <ksvc_cryptokeyversion.pb.h>
#include <ksvc_keyring.pb.h>

#include <shared_mutex>
#include <memory>
#include <variant>
#include <cassert>

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
    std::mutex                          d_mutex;
    ResultStatus                        d_status = ResultStatus::e_waiting;
    TypeSP                              d_object;
    std::vector<ResultFunction<TypeSP>> d_waitList;

    // MANIPULATORS
    bool getValue(ResultFunction<std::shared_ptr<T>> result);
    // Calls the specified 'result' some time in the future with the cached
    // value. Note that the value might not yet be available, in which case it
    // will wait for the backend to provide it. The result could also be called
    // with an 'e_timedout' status. Return 'true' when 'result' was called,
    // 'false' otherwise.

    void updateValue(const ResultStatus &status, std::shared_ptr<T> value);
    // Update with the specified 'status' and the specified 'value'. Call all
    // waitlist function.
  };

  typedef std::variant<CacheType<KeyRing>, CacheType<CryptoKey>> CacheObject;
  
  typedef std::unordered_map<std::string, std::shared_ptr<CacheObject>>
      CacheMap;

  // DATA
  std::shared_mutex d_mutex;
  CacheMap          d_cache;
  KeyStore *        d_backingKeyStore;

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
  createCacheValue(const ResultFunction<std::shared_ptr<T>> &result,
                   const std::string &                       name,
                   bool *                                    created);
  // Create cache value with the specified 'name' and add the specified 'result'
  // to its wait list. If there already exists an object with 'name' we do not
  // add 'result' to the wait list. Store 'true' into the specified 'created' if
  // we created a newcache object, 'false' otherwise'. Return the new or
  // existing cache object. Note that if we created the cache object, this means
  // it's value was not queried from the backend yet, which then needs to be
  // done.

  template <class T>
  std::shared_ptr<CacheObject>
  getCacheValue(const ResultFunction<std::shared_ptr<T>> &result,
                const std::string &                       name,
                bool *                                    created);
  // Cause the specified 'result' to be called at some point in the future with
  // the value of the object with the specified 'name'. Store 'true' into the
  // specified 'created' if we created the cache object, 'false' otherwise. Note
  // that if we created the cache object, this means it's value was not queried
  // from the backend yet, which then needs to be done.

  template <class T>
  void updateCacheValue(const ResultStatus &         status,
                        std::shared_ptr<T>           value,
                        std::shared_ptr<CacheObject> cacheObject);
  // Asynchronously called by the backing key store with the specified 'status'
  // and the specified 'value' for the specified 'cacheObject'.

public:
  // CREATORS
  CachingKeyStore(KeyStore *backingKeyStore);
  // Create a caching key store with the specified 'backingKeyStore'. Note that
  // this does not take ownership of 'backingKeyStore'.

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
                  std::string                              name) override;
  // Get key ring with the specified 'name'. Call the specified 'result' with
  // the key ring or with the 'e_notFound' status code.

  void getCryptoKey(ResultFunction<std::shared_ptr<CryptoKey>> result,
                    std::string name) override;
  // Get crypto key with the specified 'name'. Call the specified 'result' with
  // the crypto key or with the 'e_notFound' status code.
};

// --------------------------------
// Class CachingKeyStore::CacheType
// --------------------------------

template <class T>
bool CachingKeyStore::CacheType<T>::getValue(
    ResultFunction<std::shared_ptr<T>> result)
{
  auto guard = std::unique_lock(d_mutex);
  if (ResultStatus::e_waiting != d_status) {
    result(d_status, d_object);
    return true;
  }

  d_waitList.emplace_back(std::move(result));
  return false;
}

template <class T>
void CachingKeyStore::CacheType<T>::updateValue(const ResultStatus &status,
                                                std::shared_ptr<T>  value)
{
  std::vector<ResultFunction<TypeSP>> waitList;

  {
    auto guard = std::unique_lock(d_mutex);
    d_status   = status;
    d_object   = value;
    std::swap(waitList, d_waitList);
  }

  for (ResultFunction<TypeSP> &result : waitList) {
    result(status, value);
  }
}

// ---------------------
// Class CachingKeyStore
// ---------------------

template <class T>
std::shared_ptr<CachingKeyStore::CacheObject>
CachingKeyStore::createCacheObject(const std::string &name, bool *created)
{
  auto guard = std::unique_lock(d_mutex);
  auto [iter, res] = d_cache.emplace(
      name, new CacheObject(std::in_place_type_t<CacheType<T>>()));
  *created = res;
  return iter->second;
}

template <class T>
std::shared_ptr<CachingKeyStore::CacheObject> CachingKeyStore::createCacheValue(
    const ResultFunction<std::shared_ptr<T>> &result,
    const std::string &                       name,
    bool *                                    created)
{
  std::shared_ptr<CacheObject> object = std::move(getCacheObject(name));
  *created                            = false;

  if (object) {
    // Cache object already exists.
    return std::move(object);
  }
  
  object = std::move(createCacheObject<T>(name, created));

  if (!*created || !std::holds_alternative<CacheType<T>>(*object)) {
    // Object already exists in cache or object holds invalid type.
    assert(!*created);
    return std::move(object);
  }
  
  if (std::get<CacheType<T>>(*object).getValue(result)) {
    // This should not happen. We created the object, so no other concurrent
    // call should have been able to ask for a value from the backend.
    assert(false);
  }

  return std::move(object);
}

template <class T>
std::shared_ptr<CachingKeyStore::CacheObject>
CachingKeyStore::getCacheValue(const ResultFunction<std::shared_ptr<T>> &result,
                               const std::string &                       name,
                               bool *created)
{
  std::shared_ptr<CacheObject> object  = std::move(getCacheObject(name));
  *created                             = false;

  if (!object) {
    object = std::move(createCacheObject<T>(name, created));
  }

  if (!std::holds_alternative<CacheType<T>>(*object)) {
    // Cache object holds invalid type.
    assert(!*created);
    result(ResultStatus::e_notFound, nullptr);
    return nullptr;
  }

  std::get<CacheType<T>>(*object).getValue(result);

  return std::move(object);
}
  
template <class T>
void CachingKeyStore::updateCacheValue(const ResultStatus &         status,
                                       std::shared_ptr<T>           value,
                                       std::shared_ptr<CacheObject> cacheObject)
{
  assert(std::holds_alternative<CacheType<T>>(*cacheObject));
  std::get<CacheType<T>>(*cacheObject).updateValue(status, std::move(value));
}

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_CACHINGKEYSTORE

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
