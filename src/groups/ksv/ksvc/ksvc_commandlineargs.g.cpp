// ksvc_commandlineargs.t.cpp                                         -*-c++-*-
#include <ksvc_commandlineargs.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::ksvc;

TEST(CommandlineArgsTest, addShort) {
  // TEST ADDING A LONG ARGUMENT PAIR
  CommandlineArgs obj;
  obj.parseShort("c", "test");
  ASSERT_EQ(1, obj.configFiles().size());
  ASSERT_EQ("test", obj.configFiles().front());
}

TEST(CommandlineArgsTest, addLong) {
  // TEST ADDING A LONG ARGUMENT PAIR
  CommandlineArgs obj;
  obj.parseLong("config", "test");
  ASSERT_EQ(1, obj.configFiles().size());
  ASSERT_EQ("test", obj.configFiles().front());
}

TEST(CommandlineArgsTest, Constructor) {
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  CommandlineArgs obj;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
