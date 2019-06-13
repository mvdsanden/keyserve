// kdadm_element.t.cpp                                                -*-c++-*-
#include <kdadm_element.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::kdadm;

TEST(ElementTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  Element obj;
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
