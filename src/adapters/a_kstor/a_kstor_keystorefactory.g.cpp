// a_kstor_keystorefactory.t.cpp                                      -*-c++-*-
#include <a_kstor_keystorefactory.h>

#include <ksvc_configuration.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::a_kstor;

TEST(KeyStoreFactoryTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  ksvc::KeyStoreConfig config;
  KeyStoreFactory obj(config);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
