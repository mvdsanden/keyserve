// ksvc_cachingkeystore.t.cpp                                         -*-c++-*-
#include <ksvc_cachingkeystore.h>

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
  // MANIPULATORS
  void createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                     std::string                              parent,
                     std::string                              keyRingId,
                     KeyRing                                  keyRing) override
  {
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
    auto [iter, res] = d_cryptoKeys.emplace(parent + "/" + cryptoKeyId,
                                            new CryptoKey(cryptoKey));
    result(res ? ResultStatus::e_success : ResultStatus::e_exists,
           iter->second);
  }

  void getKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                  std::string                              name) override
  {
    auto i = d_keyRings.find(name);

    if (d_keyRings.end() == i) {
      result(ResultStatus::e_notFound, nullptr);
    }

    result(ResultStatus::e_success, i->second);
  }

  void getCryptoKey(ResultFunction<std::shared_ptr<CryptoKey>> result,
                    std::string                                name) override
  {
    auto i = d_cryptoKeys.find(name);

    if (d_cryptoKeys.end() == i) {
      result(ResultStatus::e_notFound, nullptr);
    }

    result(ResultStatus::e_success, i->second);
  }
};

class TestingKeyStoreAsync : public KeyStore
{

  std::mutex       d_mutex;
  TestingKeyStore *d_backingKeyStore;

public:
  // MANIPULATORS
  void createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                     std::string                              parent,
                     std::string                              keyRingId,
                     KeyRing                                  keyRing) override
  {
    std::async(
        std::launch::async,
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
            std::move(keyRing)));
  }

  void createCryptoKey(
      ResultFunction<std::shared_ptr<CryptoKey>> result,
      std::string                                parent,
      std::string                                cryptoKeyId,
      CryptoKey                                  cryptoKey,
      std::shared_ptr<CryptoKeyVersion> cryptoKeyVersion = nullptr) override
  {
    std::async(
        std::launch::async,
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
            std::move(cryptoKey)));
  }

  void getKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                  std::string                              name) override
  {
    std::async(std::launch::async,
               std::bind(
                   [this](auto result, auto name) {
                     auto guard = std::unique_lock(d_mutex);
                     d_backingKeyStore->getKeyRing(std::move(result),
                                                   std::move(name));
                   },
                   std::move(result),
                   std::move(name)));
  }

  void getCryptoKey(ResultFunction<std::shared_ptr<CryptoKey>> result,
                    std::string                                name) override
  {
    std::async(std::launch::async,
               std::bind(
                   [this](auto result, auto name) {
                     auto guard = std::unique_lock(d_mutex);
                     d_backingKeyStore->getCryptoKey(std::move(result),
                                                     std::move(name));
                   },
                   std::move(result),
                   std::move(name)));
  }
};


TEST(CachingKeyStoreTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  TestingKeyStore backing;
  CachingKeyStore obj(&backing);
}

TEST(CachingKeyStoreTest, createKeyRing)
{
  TestingKeyStore backing;
  CachingKeyStore obj(&backing);

  std::string name = "projects/test/locations/A/keyRings/test1";

  KeyRing keyRing;
  keyRing.set_name(name);

  std::atomic<size_t> count = 0;

  obj.createKeyRing(
      [&](auto status, auto keyRing) {
        ASSERT_EQ(ResultStatus::e_success, status);
        ASSERT_TRUE(keyRing);
	ASSERT_EQ(name, keyRing->name());
	++count;
      },
      "projects/test/locations/A/keyRings",
      "test1",
      keyRing);

  obj.createKeyRing(
      [&](auto status, auto keyRing) {
        ASSERT_EQ(ResultStatus::e_exists, status);
	++count;
      },
      "projects/test/locations/A/keyRings",
      "test1",
      keyRing);
  
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  ASSERT_EQ(count, 2);
}

TEST(CachingKeyStoreTest, createCryptoKey)
{
  TestingKeyStore backing;
  CachingKeyStore obj(&backing);

  std::string name = "projects/test/locations/A/cryptoKeys/test1";

  CryptoKey cryptoKey;
  cryptoKey.set_name(name);

  std::atomic<size_t> count = 0;

  obj.createCryptoKey(
      [&](auto status, auto cryptoKey) {
        ASSERT_EQ(ResultStatus::e_success, status);
        ASSERT_TRUE(cryptoKey);
	ASSERT_EQ(name, cryptoKey->name());
	++count;
      },
      "projects/test/locations/A/cryptoKeys",
      "test1",
      cryptoKey);

  //  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  //  ASSERT_EQ(count, 1);

  obj.createCryptoKey(
      [&](auto status, auto cryptoKey) {
        ASSERT_EQ(ResultStatus::e_exists, status);
	++count;
      },
      "projects/test/locations/A/cryptoKeys",
      "test1",
      cryptoKey);

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  ASSERT_EQ(count, 2);
}


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
