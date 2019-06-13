// kdadm_element.t.cpp                                                -*-c++-*-
#include <kdadm_element.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::kdadm;

TEST(ElementTest, getElementByTagName)
{
  // TEST GET ELEMENT BY TAG NAME
  Element obj;
}

TEST(ElementTest, setValue)
{
  // TEST SET VALUE
  Element obj;
  obj.setValue("test");
  ASSERT_TRUE(obj.isValueType());
  ASSERT_FALSE(obj.isElementType());
  ASSERT_EQ("test", obj.tag());
}

TEST(ElementTest, setTag)
{
  // TEST SET TAG
  Element obj;
  obj.setTag("test");
  ASSERT_TRUE(obj.isElementType());
  ASSERT_FALSE(obj.isValueType());
  ASSERT_EQ("test", obj.tag());
}

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
  ASSERT_FALSE(obj.isValueType());
  ASSERT_FALSE(obj.isElementType());
  ASSERT_TRUE(obj.children().empty());  
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
