// ksvc_cachingkeystore.t.cpp                                         -*-c++-*-
#include <ksvc_cachingkeystore.h>
#include <ksvc_configuration.h>

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


TEST(CachingKeyStoreTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  KeyStoreConfig  config;
  TestingKeyStore backing;
  CachingKeyStore obj(&backing, config);
}

TEST(CachingKeyStoreTest, createKeyRing)
{
  KeyStoreConfig  config;
  TestingKeyStore backing;
  CachingKeyStore obj(&backing, config);

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
  
  ASSERT_EQ(count, 2);
}

TEST(CachingKeyStoreTest, createCryptoKey)
{
  KeyStoreConfig  config;
  TestingKeyStore backing;
  CachingKeyStore obj(&backing, config);

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

  obj.createCryptoKey(
      [&](auto status, auto cryptoKey) {
        ASSERT_EQ(ResultStatus::e_exists, status);
	++count;
      },
      "projects/test/locations/A/cryptoKeys",
      "test1",
      cryptoKey);

  ASSERT_EQ(count, 2);
}

TEST(CachingKeyStoreTest, createKeyRingAsync)
{
  KeyStoreConfig       config;
  TestingKeyStore      backing;
  TestingKeyStoreAsync backingAsync(&backing);
  CachingKeyStore      obj(&backingAsync, config);

  std::string name = "projects/test/locations/A/keyRings/test1";

  KeyRing keyRing;
  keyRing.set_name(name);

  std::atomic<size_t> count = 0;

  obj.createKeyRing(
      [&](auto status, auto keyRing) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ASSERT_EQ(ResultStatus::e_success, status);
        ASSERT_TRUE(keyRing);
	ASSERT_EQ(name, keyRing->name());
	++count;
      },
      "projects/test/locations/A/keyRings",
      "test1",
      keyRing);

  ASSERT_EQ(count, 0);
  
  obj.createKeyRing(
      [&](auto status, auto keyRing) {
        ASSERT_EQ(ResultStatus::e_exists, status);
	++count;
      },
      "projects/test/locations/A/keyRings",
      "test1",
      keyRing);
  
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  ASSERT_EQ(count, 2);

  obj.createKeyRing(
      [&](auto status, auto keyRing) {
        ASSERT_EQ(ResultStatus::e_exists, status);
	++count;
      },
      "projects/test/locations/A/keyRings",
      "test1",
      keyRing);  
}

TEST(CachingKeyStoreTest, createCryptoKeyAsync)
{
  KeyStoreConfig       config;
  TestingKeyStore      backing;
  TestingKeyStoreAsync backingAsync(&backing);
  CachingKeyStore      obj(&backingAsync, config);

  std::string name = "projects/test/locations/A/cryptoKeys/test1";

  CryptoKey cryptoKey;
  cryptoKey.set_name(name);

  std::atomic<size_t> count = 0;

  obj.createCryptoKey(
      [&](auto status, auto cryptoKey) {
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ASSERT_EQ(ResultStatus::e_success, status);
        ASSERT_TRUE(cryptoKey);
	ASSERT_EQ(name, cryptoKey->name());
	++count;
      },
      "projects/test/locations/A/cryptoKeys",
      "test1",
      cryptoKey);

  ASSERT_EQ(count, 0);
  
  obj.createCryptoKey(
      [&](auto status, auto cryptoKey) {
        ASSERT_EQ(ResultStatus::e_exists, status);
	++count;
      },
      "projects/test/locations/A/cryptoKeys",
      "test1",
      cryptoKey);

  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  ASSERT_EQ(count, 2);

  obj.createCryptoKey(
      [&](auto status, auto cryptoKey) {
        ASSERT_EQ(ResultStatus::e_exists, status);
	++count;
      },
      "projects/test/locations/A/cryptoKeys",
      "test1",
      cryptoKey);
}

TEST(CachingKeyStoreTest, generationTest)
{
  KeyStoreConfig       config;
  config.maxCachedObjects() = 1000;

  TestingKeyStore      backing;
  CachingKeyStore      obj(&backing, config);

  std::string parent = "projects/test/locations/A/cryptoKeys";
  std::string id     = "test";
  std::string name   = parent + "/" + id;

  ASSERT_EQ(backing.d_createCount, 0);

  for (size_t i = 1; i <= 1001; ++i) {
    std::ostringstream s;
    s << id << i;

    CryptoKey cryptoKey;
    cryptoKey.set_name(s.str());

    obj.createCryptoKey(
        [&](auto status, auto cryptoKey) {
          ASSERT_EQ(ResultStatus::e_success, status);
        },
        parent,
        s.str(),
        cryptoKey);
  }

  ASSERT_EQ(backing.d_createCount, 1001);
  ASSERT_EQ(backing.d_getCount, 0);

  for (size_t i = 1001; i >= 1; --i) {
    std::ostringstream s;
    s << name << i;

    obj.getCryptoKey(
        [&](auto status, auto cryptoKey) {
          ASSERT_EQ(ResultStatus::e_success, status)
              << "Got status " << status << " for " << s.str();
        },
        s.str());
  }

  ASSERT_EQ(backing.d_createCount, 1001);
  ASSERT_EQ(backing.d_getCount, 1);
}


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
