// kdadp_xmldocumentparser.t.cpp                                      -*-c++-*-
#include <kdadp_xmldocumentparser.h>

#include <kdadm_element.h>
#include <kdadm_document.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::kdadp;

TEST(XmlDocumentParserTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  XmlDocumentParser obj;
}

TEST(XmlDocumentParserTest, Parse)
{
  // TEST PARSE
  XmlDocumentParser obj;
  kdadm::Document   doc;
  std::string xml = "<root><test>hallo this is\n a test</test><one><two></two></one></root>";
  std::istringstream stream(xml);
  ASSERT_TRUE(obj.parse(&doc, stream));
  ASSERT_EQ("root", doc.root()->tag());
  ASSERT_EQ(2, doc.root()->children().size());
  ASSERT_EQ("test", doc.root()->children()[0]->tag());
  ASSERT_EQ("one", doc.root()->children()[1]->tag());
  ASSERT_EQ("hallo this is\n a test", doc.root()->children()[0]->children()[0]->value());
  ASSERT_EQ("two", doc.root()->children()[2]->children()[0]->tag());
}


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
