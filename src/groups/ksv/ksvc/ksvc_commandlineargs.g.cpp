// ksvc_commandlineargs.t.cpp                                         -*-c++-*-
#include <ksvc_commandlineargs.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::ksvc;

namespace {

  template <typename... Args>
  const std::array<const char *, sizeof...(Args)> to_args(Args... args)
  {
    return {args...};
  }

} // anonymouse namespace

/*
TEST(CommandlineArgsTest, addShort_Unknown) {
  // TEST ADDING A LONG ARGUMENT PAIR
  CommandlineArgs obj;
  ASSERT_EQ(-1, obj.parseShort(";", std::array<const char *, 1>{"test"}));
  ASSERT_EQ(0, obj.configFiles().size());
}

TEST(CommandlineArgsTest, addLong_Unknown) {
  // TEST ADDING A LONG ARGUMENT PAIR
  CommandlineArgs obj;
  ASSERT_EQ(-1, obj.parseLong("bla", std::array<const char *, 1>{"test"}));
  ASSERT_EQ(0, obj.configFiles().size());
}

TEST(CommandlineArgsTest, addShort) {
  // TEST ADDING A LONG ARGUMENT PAIR
  CommandlineArgs obj;
  ASSERT_EQ(1, obj.parseShort("c", std::array<const char *, 1>{"test"}));
  ASSERT_EQ(1, obj.configFiles().size());
  ASSERT_EQ("test", obj.configFiles().front());
}
*/

TEST(CommandlineArgsTest, parseConfigLong) {
  // TEST ADDING A LONG ARGUMENT PAIR
  // std::vector<const char *> args;
  // args.push_back("--config");
  // args.push_back("test");

  //  CommandlineArgs obj = CommandlineArgsUtil::parse(args);
  CommandlineArgs obj = CommandlineArgsUtil::parse(to_args("--config", "test")); 
  ASSERT_EQ(1, obj.configFiles().size());
  ASSERT_EQ("test", obj.configFiles().front());
}

// TEST(CommandlineArgsTest, appendPositional) {
//   // TEST ADDING A POSITIONAL ARGUMENT
//   CommandlineArgs obj;
//   ASSERT_EQ(0, obj.positional().size());
//   obj.appendPositional("test");
//   ASSERT_EQ(1, obj.positional().size());
//   ASSERT_EQ("test", obj.positional().front());
// }

// TEST(CommandlineArgsTest, appendConfigFile) {
//   // TEST ADDING A CONFIG FILE ARGUMENT
//   CommandlineArgs obj;
//   ASSERT_EQ(0, obj.configFiles().size());
//   obj.appendConfigFile("test");
//   ASSERT_EQ(1, obj.configFiles().size());
//   ASSERT_EQ("test", obj.configFiles().front());
// }

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
