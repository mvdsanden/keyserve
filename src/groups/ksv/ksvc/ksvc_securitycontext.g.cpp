// ksvc_securitycontext.t.cpp                                         -*-c++-*-
#include <ksvc_securitycontext.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::ksvc;

class TestingSecurityContext : public SecurityContext
{  
public:
  bool d_result = true;

  virtual void validateParent(std::function<void(bool)> result,
                              std::string               parent) const
  {
    result(d_result);
  }
};

TEST(SecurityContextTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  TestingSecurityContext obj;
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
