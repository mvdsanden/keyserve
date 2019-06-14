// a_xml_saxparser.t.cpp                                              -*-c++-*-
#include <a_xml_saxparser.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::a_xml;

struct MockDocumentHandler : public kdadp::SaxDocumentHandler
{
  typedef std::pair<std::string, std::string> Attribute;
  typedef gsl::span<Attribute>                Attributes;

  std::vector<std::pair<std::string, std::vector<Attribute>>> d_startElements;
  std::vector<std::string> d_text;
  std::vector<std::string> d_endElements;
  std::vector<std::string> d_comments;
  
  void startDocument() override
  {
  }

  void startElement(const std::string& name, const Attributes& attributes) override
  {
    d_startElements.emplace_back(std::make_pair(name, std::vector(attributes.begin(), attributes.end())));
  }

  void characterData(const std::string& data) override
  {
    d_text.emplace_back(data);
  }

  void comment(const std::string& data) override
  {
    d_comments.emplace_back(data);
  }
  
  void endElement(const std::string& name) override
  {
    d_endElements.emplace_back(name);
  }

  void endDocument() override
  {
  }
};

TEST(SaxParserTest, ParseStream)
{  
  // TEST PARSING
  {
    MockDocumentHandler handler;
    SaxParser obj;
    obj.setDocumentHandler(&handler);
    std::string xml = "<root name='test'><one>two ten\neleven</one><three/></root>";
    std::istringstream stream(xml);
    ASSERT_TRUE(obj.parse(stream));
    ASSERT_EQ(3, handler.d_startElements.size());
    ASSERT_EQ("root", handler.d_startElements[0].first);
    ASSERT_EQ("name", handler.d_startElements[0].second[0].first);
    ASSERT_EQ("test", handler.d_startElements[0].second[0].second);
    ASSERT_EQ("one", handler.d_startElements[1].first);
    ASSERT_EQ(3, handler.d_text.size());
    ASSERT_EQ("two ten", handler.d_text[0]);
    ASSERT_EQ("\n", handler.d_text[1]);
    ASSERT_EQ("eleven", handler.d_text[2]);
    ASSERT_EQ("three", handler.d_startElements[2].first);
    ASSERT_EQ(3, handler.d_endElements.size());
    ASSERT_EQ("one", handler.d_endElements[0]);
    ASSERT_EQ("three", handler.d_endElements[1]);
    ASSERT_EQ("root", handler.d_endElements[2]);
  }
}


TEST(SaxParserTest, ParseBuffer)
{  
  // TEST PARSING
  {
    MockDocumentHandler handler;
    SaxParser obj;
    obj.setDocumentHandler(&handler);
    std::string xml = "<root name='test'><one>two ten\neleven</one><three/></root>";
    ASSERT_TRUE(obj.parse(xml));
    ASSERT_EQ(3, handler.d_startElements.size());
    ASSERT_EQ("root", handler.d_startElements[0].first);
    ASSERT_EQ("name", handler.d_startElements[0].second[0].first);
    ASSERT_EQ("test", handler.d_startElements[0].second[0].second);
    ASSERT_EQ("one", handler.d_startElements[1].first);
    ASSERT_EQ(3, handler.d_text.size());
    ASSERT_EQ("two ten", handler.d_text[0]);
    ASSERT_EQ("\n", handler.d_text[1]);
    ASSERT_EQ("eleven", handler.d_text[2]);
    ASSERT_EQ("three", handler.d_startElements[2].first);
    ASSERT_EQ(3, handler.d_endElements.size());
    ASSERT_EQ("one", handler.d_endElements[0]);
    ASSERT_EQ("three", handler.d_endElements[1]);
    ASSERT_EQ("root", handler.d_endElements[2]);
  }
}


TEST(SaxParserTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  SaxParser obj;
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
