// ksvc_keymanager.t.cpp                                              -*-c++-*-
#include <ksvc_keymanager.h>
#include <ksvc_configuration.h>
#include <ksvc_crypto.h>
#include <ksvc_keystore.h>
#include <ksvc_keyring.pb.h>
#include <ksvc_cryptokey.pb.h>
#include <ksvc_cryptokeyversion.pb.h>
#include <ksvc_cryptokeyversiontemplate.pb.h>

#include <google/protobuf/util/time_util.h>

#include <thread>
#include <future>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::ksvc;

class TestingKeyStore : public KeyStore
{

  std::unordered_map<std::string, std::shared_ptr<KeyRing>>   d_keyRings;
  std::unordered_map<std::string, std::shared_ptr<CryptoKey>> d_cryptoKeys;

public:
  // PUBLIC DATA
  size_t d_createCount = 0;
  size_t d_getCount    = 0;

  // MANIPULATORS
  void createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                     std::string                              parent,
                     std::string                              keyRingId,
                     KeyRing                                  keyRing) override
  {
    ++d_createCount;
    
    auto [iter, res] =
        d_keyRings.emplace(parent + "/" + keyRingId, new KeyRing(keyRing));

    result(res ? ResultStatus::e_success : ResultStatus::e_exists, iter->second);
  }

  void createCryptoKey(
      ResultFunction<std::shared_ptr<CryptoKey>> result,
      std::string                                parent,
      std::string                                cryptoKeyId,
      CryptoKey                                  cryptoKey,
      std::shared_ptr<CryptoKeyVersion> cryptoKeyVersion = nullptr) override
  {
    ++d_createCount;

    std::string name = parent + "/" + cryptoKeyId;

    //    std::cout << "BACKING KEY STORE: create '" << name << "'.\n";
    
    auto [iter, res] = d_cryptoKeys.emplace(name,
                                            new CryptoKey(cryptoKey));
    result(res ? ResultStatus::e_success : ResultStatus::e_exists,
           iter->second);
  }

  void getKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                  std::string                              name) override
  {
    ++d_getCount;
    
    auto i = d_keyRings.find(name);

    if (d_keyRings.end() == i) {
      result(ResultStatus::e_notFound, nullptr);
    }

    result(ResultStatus::e_success, i->second);
  }

  void getCryptoKey(ResultFunction<std::shared_ptr<CryptoKey>> result,
                    std::string                                name) override
  {
    ++d_getCount;

    //    std::cout << "BACKING KEY STORE: get '" << name << "': ";
    
    auto i = d_cryptoKeys.find(name);

    if (d_cryptoKeys.end() == i) {
      //      std::cout << "NOT FOUND\n";
      result(ResultStatus::e_notFound, nullptr);
    }

    //    std::cout << "FOUND\n";
    result(ResultStatus::e_success, i->second);
  }
};

class TestingKeyStoreAsync : public KeyStore
{

  std::mutex       d_mutex;
  KeyStore *       d_backingKeyStore;

public:
  // CREATORS
  TestingKeyStoreAsync(KeyStore *backingKeyStore)
    : d_backingKeyStore(backingKeyStore)
  {}

  // MANIPULATORS
  void createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                     std::string                              parent,
                     std::string                              keyRingId,
                     KeyRing                                  keyRing) override
  {
    std::thread(
        std::bind(
            [this](auto result, auto parent, auto keyRingId, auto keyRing) {
              auto guard = std::unique_lock(d_mutex);
              d_backingKeyStore->createKeyRing(std::move(result),
					       std::move(parent),
					       std::move(keyRingId),
					       std::move(keyRing));
            },
            std::move(result),
            std::move(parent),
            std::move(keyRingId),
            std::move(keyRing))).detach();
  }

  void createCryptoKey(
      ResultFunction<std::shared_ptr<CryptoKey>> result,
      std::string                                parent,
      std::string                                cryptoKeyId,
      CryptoKey                                  cryptoKey,
      std::shared_ptr<CryptoKeyVersion> cryptoKeyVersion = nullptr) override
  {
    std::thread(
        std::bind(
            [this](auto result, auto parent, auto cryptoKeyId, auto cryptoKey) {
              auto guard = std::unique_lock(d_mutex);
              d_backingKeyStore->createCryptoKey(std::move(result),
					       std::move(parent),
					       std::move(cryptoKeyId),
					       std::move(cryptoKey));
            },
            std::move(result),
            std::move(parent),
            std::move(cryptoKeyId),
            std::move(cryptoKey))).detach();
  }

  void getKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                  std::string                              name) override
  {
    std::thread(std::bind(
        [this](auto result, auto name) {
          auto guard = std::unique_lock(d_mutex);
          d_backingKeyStore->getKeyRing(std::move(result), std::move(name));
        },
        std::move(result),
        std::move(name))).detach();
  }

  void getCryptoKey(ResultFunction<std::shared_ptr<CryptoKey>> result,
                    std::string                                name) override
  {
    std::thread(std::bind(
        [this](auto result, auto name) {
          auto guard = std::unique_lock(d_mutex);
          d_backingKeyStore->getCryptoKey(std::move(result), std::move(name));
        },
        std::move(result),
        std::move(name))).detach();
  }
};

class TestingCrypto : public Crypto {
public:
  void createCryptoKey(ResultFunction<std::shared_ptr<CryptoKeyVersion>> result,
                       CryptoKeyVersionTemplate versionTemplate) override
  {
    using TimeUtil = google::protobuf::util::TimeUtil;

    auto version = std::make_shared<ksvc::CryptoKeyVersion>();
    version->set_algorithm(versionTemplate.algorithm());
    version->set_createtime(TimeUtil::ToString(TimeUtil::GetCurrentTime()));

    result(ksvc::ResultStatus::e_success, std::move(version));
  }
};

TEST(KeyManagerTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  Configuration config;
  std::unique_ptr<KeyManager> obj(KeyManager::create(nullptr, nullptr, config));
}

TEST(KeyManagerTest, createKeyRing)
{
  Configuration               config;
  TestingKeyStore             keyStore;
  TestingCrypto               crypto;
  std::unique_ptr<KeyManager> obj(KeyManager::create(&keyStore, &crypto, config));

  std::string parent = "projects/test/locations/A/keyRings";
  std::string id     = "test";
  std::string name   = parent + "/" + id;

  ksvc::KeyRing keyRing;
  keyRing.set_name(name);

  // obj->getKeyRing(
  //     [&](auto status, auto object) {
  //       ASSERT_EQ(status, ksvc::ResultStatus::e_notFound);
  //     },
  //     name);
  
  obj->createKeyRing(
      [&](auto status, auto object) {
        ASSERT_EQ(status, ksvc::ResultStatus::e_success);
        ASSERT_EQ(object->name(), name);
      },
      parent,
      id,
      keyRing);

  // obj->getKeyRing(
  //     [&](auto status, auto object) {
  //       ASSERT_EQ(status, ksvc::ResultStatus::e_success);
  //     },
  //     name);
}

TEST(KeyManagerTest, createCryptoKey)
{
  Configuration               config;
  TestingKeyStore             keyStore;
  TestingCrypto               crypto;
  std::unique_ptr<KeyManager> obj(KeyManager::create(&keyStore, &crypto, config));

  std::string parent = "projects/test/locations/A/keyRings";
  std::string id     = "test";
  std::string name   = parent + "/" + id;

  CryptoKey cryptoKey;
  
  std::array<ksvc::CryptoKeyVersionAlgorithm, 2> algos = {
      ksvc::CRYPTO_KEY_VERSION_ALOGRITHM_UNSPECIFIED,
      ksvc::SYMMETRIC_ENCRYPTION};

  for (auto algorithm : algos) {
    name += "0";
    
    cryptoKey.mutable_versiontemplate()->set_algorithm(algorithm);

    obj->createCryptoKey(
        [&](auto status, auto cryptoKey) {
          ASSERT_EQ(status, ksvc::ResultStatus::e_success);
        },
        parent, id, cryptoKey);
  }
  
}


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
