// m_cfgen_validator.t.cpp                                        -*-c++-*-
#include <m_cfgen_validator.h>

#include <kdadm_element.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::m_cfgen;

TEST(ValidatorTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  CommandlineArgs args;
  Validator obj(args);
}

TEST(ValidatorTest, Parameters)
{
  // EXPECT CONFIG PARAMETERS
  kdadm::Document doc;

  {
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("ns", "test");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_TRUE(obj.validate(&doc));
  }

  {
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("ns", "test");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_FALSE(obj.validate(&doc));
  }

  {
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_FALSE(obj.validate(&doc));
  }

  {
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("ns", "test");
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_FALSE(obj.validate(&doc));
  }

  
}

TEST(ValidatorTest, InternalTypes)
{
  // INTERNAL TYPE
  kdadm::Document doc;

  {
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("ns", "test");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    auto i1 = root->children().emplace_back(kdadm::Element::createElement("xs:internalType"));
    i1->attributes().emplace_back("name", "test");
    auto c1 = i1->children().emplace_back(kdadm::Element::createElement("xs:cpp"));
    c1->attributes().emplace_back("type", "test");
    c1->attributes().emplace_back("include", "test");
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_TRUE(obj.validate(&doc));
  }

  { // NO INTERNAL TYPE NAME
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("ns", "test");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    auto i1 = root->children().emplace_back(kdadm::Element::createElement("xs:internalType"));
    auto c1 = i1->children().emplace_back(kdadm::Element::createElement("xs:cpp"));
    c1->attributes().emplace_back("type", "test");
    c1->attributes().emplace_back("include", "test");
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_FALSE(obj.validate(&doc));
  }
}

TEST(ValidatorTest, ComplexTypes)
{
  // INTERNAL TYPE
  kdadm::Document doc;

  {
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("ns", "test");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    auto c1 = root->children().emplace_back(kdadm::Element::createElement("xs:complexType"));
    c1->attributes().emplace_back("name", "test");
    auto s1 = c1->children().emplace_back(kdadm::Element::createElement("xs:sequence"));
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_TRUE(obj.validate(&doc));
  }

  { // NO NAME
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("ns", "test");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    auto c1 = root->children().emplace_back(kdadm::Element::createElement("xs:complexType"));
    auto s1 = c1->children().emplace_back(kdadm::Element::createElement("xs:sequence"));
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_FALSE(obj.validate(&doc));
  }

  { // NO SEQUENCE
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("ns", "test");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    auto c1 = root->children().emplace_back(kdadm::Element::createElement("xs:complexType"));
    c1->attributes().emplace_back("name", "test");
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_FALSE(obj.validate(&doc));
  }
  
}

TEST(ValidatorTest, Element)
{
  // ELEMENT
  kdadm::Document doc;

  {
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("ns", "test");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    auto c1 = root->children().emplace_back(kdadm::Element::createElement("xs:element"));
    c1->attributes().emplace_back("name", "test");
    c1->attributes().emplace_back("type", "xs:string");
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_TRUE(obj.validate(&doc));
    ASSERT_EQ(c1->children().size(), 1);
    ASSERT_EQ(c1->children()[0]->tag(), "xs:internalType");
    ASSERT_GT(doc.root()->children().size(), 0);
    ASSERT_EQ(doc.root()->children().back()->tag(), "xs:internalType");
  }

  { // NO NAME
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("ns", "test");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    auto c1 = root->children().emplace_back(kdadm::Element::createElement("xs:element"));
    c1->attributes().emplace_back("type", "xs:string");
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_FALSE(obj.validate(&doc));
  }

  { // NO TYPE
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("ns", "test");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    auto c1 = root->children().emplace_back(kdadm::Element::createElement("xs:element"));
    c1->attributes().emplace_back("name", "test");
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_FALSE(obj.validate(&doc));
  }

  { // UNKNOWN TYPE
    auto root = kdadm::Element::createElement("root");
    root->attributes().emplace_back("name", "Config");
    root->attributes().emplace_back("ns", "test");
    root->attributes().emplace_back("enterpriseNs", "MvdS");
    auto c1 = root->children().emplace_back(kdadm::Element::createElement("xs:element"));
    c1->attributes().emplace_back("name", "test");
    c1->attributes().emplace_back("type", "xs:test");
    doc.setRoot(std::move(root));

    CommandlineArgs args;
    Validator obj(args);

    ASSERT_FALSE(obj.validate(&doc));
  }  
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
