// ksvc_securedkeymanager.t.cpp                                       -*-c++-*-
#include <ksvc_configuration.h>
#include <ksvc_keymanager.h>
#include <ksvc_securedkeymanager.h>
#include <ksvc_keyring.pb.h>
#include <ksvc_cryptokey.pb.h>
#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::ksvc;

class TestingKeyManager : public KeyManager {
public:
  void createKeyRing(ResultFunction<std::shared_ptr<KeyRing>> result,
                     std::string                              parent,
                     std::string                              keyRingId,
                     KeyRing                                  keyRing) override
  {
  }

  void createCryptoKey(ResultFunction<std::shared_ptr<CryptoKey>> result,
                       std::string                                parent,
                       std::string                                cryptoKeyId,
                       CryptoKey                                  cryptoKey,
                       bool skipInitialVersionCreation = false) override
  {
  }
  
};

TEST(SecuredKeyManagerTest, Constructor)
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
  SecuredKeyManager obj(&keyManager, config);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
