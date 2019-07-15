// ksvc_keymanager.t.cpp                                              -*-c++-*-
#include <ksvc_keymanager.h>
#include <ksvc_configuration.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::ksvc;

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

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
