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

TEST(CommandlineArgsTest, parseHelp) {
  // TEST CONFIG ARGUMENT
  {
    CommandlineArgs obj;
    CommandlineArgsUtil::parse(&obj, to_args("--help"));
    ASSERT_TRUE(obj.printUsage());
  }

  {
    CommandlineArgs obj;
    CommandlineArgsUtil::parse(&obj, to_args("-h"));
    ASSERT_TRUE(obj.printUsage());
  }
}

TEST(CommandlineArgsTest, mix) {
  // TEST MIXING POSITIONAL AND NON-POSITIONAL ARGUMENTS
  auto            args = to_args("1234", "--config", "test", "5678");
  CommandlineArgs obj;
  CommandlineArgsUtil::parse(&obj, args);
  ASSERT_EQ(2, obj.positional().size());
  ASSERT_EQ("1234", obj.positional()[0]);
  ASSERT_EQ("5678", obj.positional()[1]);
  ASSERT_EQ(1, obj.configFiles().size());
  ASSERT_EQ("test", obj.configFiles().front());
}

TEST(CommandlineArgsTest, parseConfig) {
  // TEST CONFIG ARGUMENT
  {
    CommandlineArgs obj;
    CommandlineArgsUtil::parse(&obj, to_args("--config", "test"));
    ASSERT_EQ(1, obj.configFiles().size());
    ASSERT_EQ("test", obj.configFiles().front());
  }

  {
    CommandlineArgs obj;
    CommandlineArgsUtil::parse(&obj, to_args("-c", "test")); 
    ASSERT_EQ(1, obj.configFiles().size());
    ASSERT_EQ("test", obj.configFiles().front());
  }
}

TEST(CommandlineArgsTest, positional) {
  // TEST POSITIONAL ARGUMENTS
  auto args =
      to_args("this", "is", "a", "test", "-asdjksaldj", "--djaskdjaskl");
  CommandlineArgs obj;
  CommandlineArgsUtil::parse(&obj, args);
  ASSERT_EQ(6, obj.positional().size());

  for (size_t i = 0; i < args.size(); ++i) {
    ASSERT_EQ(args[i], obj.positional()[i]);
  }
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
