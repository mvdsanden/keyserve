// ksvc_securitycredentials.t.cpp                                     -*-c++-*-
#include <ksvc_securitycredentials.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::ksvc;

TEST(SecurityCredentialsTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  SecurityCredentials obj;
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
