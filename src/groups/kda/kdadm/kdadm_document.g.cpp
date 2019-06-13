// kdadm_document.t.cpp                                               -*-c++-*-
#include <kdadm_document.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::kdadm;

TEST(DocumentTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  Document obj;
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
