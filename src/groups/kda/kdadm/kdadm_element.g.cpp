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
  ASSERT_EQ("test", obj.value());
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

  {
    Element::Attributes attributes;
    attributes.emplace_back("test", "one");
    attributes.emplace_back("test", "two");
    std::shared_ptr<Element> obj = Element::createElement("test", std::begin(attributes), std::end(attributes));
    ASSERT_FALSE(obj->isValueType());
    ASSERT_TRUE(obj->isElementType());
    ASSERT_TRUE(obj->children().empty());
    ASSERT_EQ("test", obj->tag());
    ASSERT_EQ(2, obj->attributes().size());
    ASSERT_EQ(obj->attributes()[0], Element::Attribute("test", "one"));
    ASSERT_EQ(obj->attributes()[1], Element::Attribute("test", "two"));
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

TEST(ElementTest, getElementsByTagName)
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

TEST(ElementTest, getFirstAttributeByName)
{
  // TEST GET FIRST ATTRIBUTE BY NAME
  Element obj;
  obj.attributes().emplace_back("one", "1");
  obj.attributes().emplace_back("two", "2");
  obj.attributes().emplace_back("one", "3");
  obj.attributes().emplace_back("two", "2");

  auto iter = obj.getFirstAttributeByName("one");
  ASSERT_EQ(iter, obj.attributes().begin());

  iter = obj.getFirstAttributeByName("two");
  ASSERT_EQ(iter->second, "2");
}

TEST(ElementUtilsTest, getElementByTagName)
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

  auto iter = ElementUtils::getElementByTagName(
      "one", obj.children().begin(), obj.children().end());
  ASSERT_EQ(obj.children().begin(), iter);
  ASSERT_EQ((*iter)->tag(), "one");

  iter = ElementUtils::getElementByTagName("one", iter + 1, obj.children().end());
  ASSERT_NE(obj.children().begin(), iter);
  ASSERT_EQ((*iter)->tag(), "one");

  iter = ElementUtils::getElementByTagName("one", iter + 1, obj.children().end());
  ASSERT_EQ(obj.children().end(), iter);
}

TEST(ElementUtilsTest, getAttributeByName)
{
  // TEST GET ATTRIBUTE BY NAME
  Element obj;
  obj.attributes().emplace_back("one", "1");
  obj.attributes().emplace_back("two", "2");
  obj.attributes().emplace_back("one", "3");
  obj.attributes().emplace_back("two", "2");

  auto iter = ElementUtils::getAttributeByName(
      "one", obj.attributes().begin(), obj.attributes().end());
  ASSERT_EQ(obj.attributes().begin(), iter);
  ASSERT_EQ(*iter, (std::make_pair<std::string, std::string>("one", "1")));

  iter = ElementUtils::getAttributeByName("one", iter + 1, obj.attributes().end());
  ASSERT_NE(obj.attributes().begin(), iter);
  ASSERT_EQ(*iter, (std::make_pair<std::string, std::string>("one", "3")));

  iter = ElementUtils::getAttributeByName("one", iter + 1, obj.attributes().end());
  ASSERT_EQ(obj.attributes().end(), iter);  
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
