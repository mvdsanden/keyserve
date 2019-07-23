// a_ksrvs_servicefactory.t.cpp                                       -*-c++-*-
#include <a_ksrvs_servicefactory.h>
#include <ksvc_configuration.h>
#include <ksvc_cryptokey.pb.h>
#include <ksvc_keymanager.h>
#include <ksvc_keyring.pb.h>
#include <ksvc_securedkeymanager.h>
#include <ksvc_securitycredentials.h>
#include <ksvc_securitymanager.h>
#include <ksvc_service.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::a_ksrvs;

class TestingKeyManager : public ksvc::KeyManager {
public:
  std::atomic<size_t> d_createKeyRingCounter   = 0;
  std::atomic<size_t> d_createCryptoKeyCounter = 0;

  void
  createKeyRing(ksvc::ResultFunction<std::shared_ptr<ksvc::KeyRing>> result,
                std::string                                          parent,
                std::string                                          keyRingId,
                ksvc::KeyRing keyRing) override
  {
    ++d_createKeyRingCounter;
  }

  void
  createCryptoKey(ksvc::ResultFunction<std::shared_ptr<ksvc::CryptoKey>> result,
                  std::string                                            parent,
                  std::string     cryptoKeyId,
                  ksvc::CryptoKey cryptoKey,
                  bool            skipInitialVersionCreation = false) override
  {
    ++d_createCryptoKeyCounter;
  }
  
};

TEST(ServiceFactoryTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  TestingKeyManager       keyManager;
  ksvc::Configuration     config;
  ksvc::SecuredKeyManager securedKeyManager(&keyManager, config);
  ksvc::SecurityManager   securityManager(&securedKeyManager);
  ServiceFactory obj(&securityManager, config);
}

TEST(ServiceFactoryTest, createServices)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  TestingKeyManager keyManager;
  ksvc::Configuration     config;

  ksvc::ServiceConfig serviceConfig;
  serviceConfig.type() = "grpc";
  config.service().emplace_back(serviceConfig);

  ksvc::SecuredKeyManager securedKeyManager(&keyManager, config);
  ksvc::SecurityManager   securityManager(&securedKeyManager);
  ServiceFactory obj(&securityManager, config);
  
  auto services = obj.createConfigured();

  ASSERT_EQ(services.size(), 1);
}


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
