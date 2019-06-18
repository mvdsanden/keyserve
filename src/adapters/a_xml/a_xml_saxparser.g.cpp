// a_xml_saxparser.t.cpp                                              -*-c++-*-
#include <a_xml_saxparser.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::a_xml;

struct MockDocumentHandler : public kdadp::SaxDocumentHandler
{
  // PUBLIC TYPES
  typedef std::pair<std::string, std::string> Attribute;
  typedef gsl::span<Attribute>                Attributes;

  // PUBLIC DATA
  std::vector<std::tuple<std::string, std::vector<Attribute>, size_t, size_t>>
                                                              d_startElements;
  std::vector<std::tuple<std::string, size_t, size_t>>        d_text;
  std::vector<std::tuple<std::string, size_t, size_t>>        d_endElements;
  std::vector<std::string>                                    d_comments;
  size_t                                                      d_lineNumber = 0;
  size_t d_columnNumber                                                    = 0;

  // MANIPULATORS
  void location(size_t lineNumber, size_t columnNumber) override
  {
    d_lineNumber   = lineNumber;
    d_columnNumber = columnNumber;
  }
  
  void startDocument() override
  {
  }

  void startElement(const std::string &name,
                    const Attributes & attributes) override
  {
    d_startElements.emplace_back(
        name,
        std::vector(attributes.begin(), attributes.end()),
        d_lineNumber,
        d_columnNumber);
  }

  void characterData(const std::string& data) override
  {
    d_text.emplace_back(data, d_lineNumber, d_columnNumber);
  }

  void comment(const std::string& data) override
  {
    d_comments.emplace_back(data);
  }
  
  void endElement(const std::string& name) override
  {
    d_endElements.emplace_back(name, d_lineNumber, d_columnNumber);
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
    ASSERT_EQ(handler.d_lineNumber, 0);
    ASSERT_EQ(handler.d_columnNumber, 0);
    ASSERT_TRUE(obj.parse(stream));
    ASSERT_EQ(3, handler.d_startElements.size());
    ASSERT_EQ("root", std::get<0>(handler.d_startElements[0]));
    ASSERT_EQ(1, std::get<2>(handler.d_startElements[0]));
    ASSERT_EQ("name", std::get<1>(handler.d_startElements[0])[0].first);
    ASSERT_EQ("test", std::get<1>(handler.d_startElements[0])[0].second);
    ASSERT_EQ("one", std::get<0>(handler.d_startElements[1]));
    ASSERT_EQ(3, handler.d_text.size());
    ASSERT_EQ("two ten", std::get<0>(handler.d_text[0]));
    ASSERT_EQ(1, std::get<1>(handler.d_text[0]));
    ASSERT_EQ("\n", std::get<0>(handler.d_text[1]));
    ASSERT_EQ("eleven", std::get<0>(handler.d_text[2]));
    ASSERT_EQ(2, std::get<1>(handler.d_text[2]));
    ASSERT_EQ("three", std::get<0>(handler.d_startElements[2]));
    ASSERT_EQ(2, std::get<2>(handler.d_startElements[2]));
    ASSERT_EQ(3, handler.d_endElements.size());
    ASSERT_EQ("one", std::get<0>(handler.d_endElements[0]));
    ASSERT_EQ(2, std::get<1>(handler.d_endElements[0]));
    ASSERT_EQ("three", std::get<0>(handler.d_endElements[1]));
    ASSERT_EQ(2, std::get<1>(handler.d_endElements[1]));
    ASSERT_EQ("root", std::get<0>(handler.d_endElements[2]));
    ASSERT_EQ(2, std::get<1>(handler.d_endElements[2]));    
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
    ASSERT_EQ(handler.d_lineNumber, 0);
    ASSERT_EQ(handler.d_columnNumber, 0);
    ASSERT_TRUE(obj.parse(xml));
    ASSERT_EQ(3, handler.d_startElements.size());
    ASSERT_EQ("root", std::get<0>(handler.d_startElements[0]));
    ASSERT_EQ(1, std::get<2>(handler.d_startElements[0]));
    ASSERT_EQ("name", std::get<1>(handler.d_startElements[0])[0].first);
    ASSERT_EQ("test", std::get<1>(handler.d_startElements[0])[0].second);
    ASSERT_EQ("one", std::get<0>(handler.d_startElements[1]));
    ASSERT_EQ(3, handler.d_text.size());
    ASSERT_EQ("two ten", std::get<0>(handler.d_text[0]));
    ASSERT_EQ(1, std::get<1>(handler.d_text[0]));
    ASSERT_EQ("\n", std::get<0>(handler.d_text[1]));
    ASSERT_EQ("eleven", std::get<0>(handler.d_text[2]));
    ASSERT_EQ(2, std::get<1>(handler.d_text[2]));
    ASSERT_EQ("three", std::get<0>(handler.d_startElements[2]));
    ASSERT_EQ(2, std::get<2>(handler.d_startElements[2]));
    ASSERT_EQ(3, handler.d_endElements.size());
    ASSERT_EQ("one", std::get<0>(handler.d_endElements[0]));
    ASSERT_EQ(2, std::get<1>(handler.d_endElements[0]));
    ASSERT_EQ("three", std::get<0>(handler.d_endElements[1]));
    ASSERT_EQ(2, std::get<1>(handler.d_endElements[1]));
    ASSERT_EQ("root", std::get<0>(handler.d_endElements[2]));
    ASSERT_EQ(2, std::get<1>(handler.d_endElements[2]));
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
