// a_kstor_memorykeystore.cpp                                         -*-c++-*-
#include <a_kstor_memorykeystore.h>

#include <ksvc_keyring.pb.h>
#include <ksvc_cryptokey.pb.h>

namespace MvdS {
namespace a_kstor {

  namespace {
    std::string makeName(const std::string& parent, const std::string& id)
    {
      std::string result;
      result.reserve(parent.size() + 1 + id.size());
      result += parent;
      result += "/";
      result += id;
      return std::move(result);
    }

    template <class T, class ObjectMap, class Mutex>
    void createObject(ksvc::ResultFunction<std::shared_ptr<T>> result,
                      std::string                              name,
                      T                                        object,
                      ObjectMap *                              objectMap,
                      Mutex *                                  mutex)
    {
      auto guard       = std::unique_lock(*mutex);
      auto [iter, res] = objectMap->emplace(
          std::move(name), std::make_shared<T>(std::move(object)));

      result(res ? ksvc::ResultStatus::e_success : ksvc::ResultStatus::e_exists,
             iter->second);
    }

    template <class T, class ObjectMap, class Mutex>
    void getObject(ksvc::ResultFunction<std::shared_ptr<T>> result,
                   const std::string &                      name,
                   ObjectMap *                              objectMap,
                   Mutex *                                  mutex)
    {
      auto guard = std::shared_lock(*mutex);
      auto iter  = objectMap->find(name);
      bool res   = (objectMap->end() != iter);
      result(res ? ksvc::ResultStatus::e_success
                 : ksvc::ResultStatus::e_notFound,
             res ? iter->second : std::shared_ptr<T>());
    }
    
  }; // anonymous namespace
  
// ---------------------
// Class: MemoryKeyStore
// ---------------------

// CREATORS
MemoryKeyStore::MemoryKeyStore(const ksvc::KeyStoreConfig &config) {}

// MANIPULATORS
void MemoryKeyStore::createKeyRing(
    ksvc::ResultFunction<std::shared_ptr<ksvc::KeyRing>> result,
    std::string                                          parent,
    std::string                                          keyRingId,
    ksvc::KeyRing                                        keyRing)
{
  std::string name = std::move(makeName(parent, keyRingId));
  createObject(std::move(result),
               std::move(name),
               std::move(keyRing),
               &d_keyRings,
               &d_keyRingsMutex);
}

void MemoryKeyStore::createCryptoKey(
    ksvc::ResultFunction<std::shared_ptr<ksvc::CryptoKey>> result,
    std::string                                            parent,
    std::string                                            cryptoKeyId,
    ksvc::CryptoKey                                        cryptoKey,
    std::shared_ptr<ksvc::CryptoKeyVersion>                cryptoKeyVersion)
{
  std::string name = std::move(makeName(parent, cryptoKeyId));
  createObject(std::move(result),
               std::move(name),
               std::move(cryptoKey),
               &d_cryptoKeys,
               &d_cryptoKeysMutex);
}

void MemoryKeyStore::getKeyRing(
    ksvc::ResultFunction<std::shared_ptr<ksvc::KeyRing>> result,
    std::string                                          name)
{
  getObject(std::move(result), std::move(name), &d_keyRings, &d_keyRingsMutex);
}

void MemoryKeyStore::getCryptoKey(
    ksvc::ResultFunction<std::shared_ptr<ksvc::CryptoKey>> result,
    std::string                                            name)
{
  getObject(
      std::move(result), std::move(name), &d_cryptoKeys, &d_cryptoKeysMutex);
}

// ACCESSORS

} // namespace a_kstor
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
