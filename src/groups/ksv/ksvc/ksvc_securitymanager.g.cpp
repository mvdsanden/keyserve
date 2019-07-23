// ksvc_securitymanager.t.cpp                                         -*-c++-*-
#include <gtest/gtest.h>
#include <ksvc_configuration.h>
#include <ksvc_cryptokey.pb.h>
#include <ksvc_keymanager.h>
#include <ksvc_keyring.pb.h>
#include <ksvc_securedkeymanager.h>
#include <ksvc_securitymanager.h>
#include <ksvc_securitycredentials.h>

#include <chrono>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::ksvc;

class TestingKeyManager : public KeyManager {
public:
  std::atomic<size_t> d_createKeyRingCounter   = 0;
  std::atomic<size_t> d_createCryptoKeyCounter = 0;

  void createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                     std::string                              parent,
                     std::string                              keyRingId,
                     KeyRing                                  keyRing) override
  {
    ++d_createKeyRingCounter;
  }

  void createCryptoKey(ResultFunction<std::shared_ptr<CryptoKey>> result,
                       std::string                                parent,
                       std::string                                cryptoKeyId,
                       CryptoKey                                  cryptoKey,
                       bool skipInitialVersionCreation = false) override
  {
    ++d_createCryptoKeyCounter;
  }
  
};

TEST(SecurityManagerTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  TestingKeyManager keyManager;
  Configuration     config;
  SecuredKeyManager securedKeyManager(&keyManager, config);
  SecurityManager   obj(&securedKeyManager);
}

TEST(SecurityManagerTest, createSession)
{
  TestingKeyManager keyManager;
  Configuration     config;
  SecuredKeyManager securedKeyManager(&keyManager, config);
  SecurityManager   obj(&securedKeyManager);
  auto credentials = std::make_unique<SecurityCredentials>();
  std::atomic<size_t> counter = 0;
  obj.createSession(
      [&](auto status, auto keyManager) {
        ASSERT_EQ(status, ResultStatus::e_success);
	ASSERT_NE(keyManager, nullptr);
	++counter;
        keyManager->createKeyRing(
            [](auto a, auto b) {}, "test/a", "b", KeyRing());
        keyManager->createCryptoKey(
            [](auto a, auto b) {}, "test/a", "b", CryptoKey());
      },
      std::move(credentials));

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  ASSERT_EQ(counter, 1);
  ASSERT_EQ(keyManager.d_createKeyRingCounter, 1);
  ASSERT_EQ(keyManager.d_createCryptoKeyCounter, 1);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
