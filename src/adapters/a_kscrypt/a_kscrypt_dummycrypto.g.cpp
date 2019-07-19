// a_kscrypt_dummycrypto.t.cpp                                        -*-c++-*-
#include <a_kscrypt_dummycrypto.h>

#include <ksvc_configuration.h>

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

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
