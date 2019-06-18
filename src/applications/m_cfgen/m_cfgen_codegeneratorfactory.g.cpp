// m_cfgen_codegeneratorfactory.t.cpp                                 -*-c++-*-
#include <m_cfgen_codegeneratorfactory.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::m_cfgen;

TEST(CodeGeneratorFactoryTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  //  CodeGeneratorFactory obj;
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
