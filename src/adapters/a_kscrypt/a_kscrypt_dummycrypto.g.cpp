// a_kscrypt_dummycrypto.t.cpp                                        -*-c++-*-
#include <a_kscrypt_dummycrypto.h>

#include <ksvc_configuration.h>

#include <ksvc_cryptokeyversiontemplate.pb.h>
#include <ksvc_cryptokeyversion.pb.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::a_kscrypt;

TEST(DummyCryptoTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  ksvc::CryptoConfig config;
  DummyCrypto obj(config);
}

TEST(DummyCryptoTest, createCryptoKey)
{
  ksvc::CryptoConfig config;
  DummyCrypto        obj(config);

  std::array<ksvc::CryptoKeyVersionAlgorithm, 2> algos = {
      ksvc::CRYPTO_KEY_VERSION_ALOGRITHM_UNSPECIFIED,
      ksvc::SYMMETRIC_ENCRYPTION};

  for (auto algorithm : algos) {
    ksvc::CryptoKeyVersionTemplate versionTemplate;
    versionTemplate.set_algorithm(algorithm);

    obj.createCryptoKey(
        [&](auto status, auto cryptoKeyVersion) {
          ASSERT_EQ(status, ksvc::ResultStatus::e_success);
          ASSERT_EQ(cryptoKeyVersion->algorithm(), versionTemplate.algorithm());
        },
        versionTemplate);
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
