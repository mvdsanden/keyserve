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
  ASSERT_FALSE(obj.isValueType());
  ASSERT_FALSE(obj.isElementType());
  ASSERT_TRUE(obj.children().empty());  
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

TEST(ElementTest, createElement)
{
  // TEST CREATE ELEMENT
  {
    std::unique_ptr<Element> obj = Element::createElement("test");
    ASSERT_EQ("test", obj->tag());
    ASSERT_FALSE(obj->isValueType());
    ASSERT_TRUE(obj->isElementType());
    ASSERT_TRUE(obj->children().empty());
  }

  {
    std::shared_ptr<Element> obj = Element::createElement("test");
    ASSERT_FALSE(obj->isValueType());
    ASSERT_TRUE(obj->isElementType());
    ASSERT_TRUE(obj->children().empty());
    ASSERT_EQ("test", obj->tag());
  }
}

TEST(ElementTest, createValue)
{
  // TEST CREATE ELEMENT
  {
    std::unique_ptr<Element> obj = Element::createValue("test");
    ASSERT_TRUE(obj->isValueType());
    ASSERT_FALSE(obj->isElementType());
    ASSERT_TRUE(obj->children().empty());
    ASSERT_EQ("test", obj->value());
  }

  {
    std::shared_ptr<Element> obj = Element::createValue("test");
    ASSERT_TRUE(obj->isValueType());
    ASSERT_FALSE(obj->isElementType());
    ASSERT_TRUE(obj->children().empty());
    ASSERT_EQ("test", obj->value());
  }
}

TEST(ElementTest, getElementByTagName)
{
  // TEST GET ELEMENT BY TAG NAME
  Element obj;
  obj.children().emplace_back(Element::createElement("one"));
  obj.children().emplace_back(Element::createElement("two"));
  obj.children().emplace_back(Element::createElement("three"));
  obj.children().emplace_back(Element::createElement("one"));
  obj.children().emplace_back(Element::createElement("Two"));
  obj.children().emplace_back(Element::createElement("Three"));
  ASSERT_EQ(6, obj.children().size());
  
  Element::Elements elements;
  elements.reserve(obj.children().size());
  obj.getElementsByTagName(std::back_inserter(elements), "one");
  ASSERT_EQ(2, elements.size());
  ASSERT_EQ("one", elements[0]->tag());
  ASSERT_EQ("one", elements[1]->tag());
}
 

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
