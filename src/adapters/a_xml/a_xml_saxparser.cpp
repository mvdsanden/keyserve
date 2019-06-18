// a_xml_saxparser.cpp                                                -*-c++-*-
#include <a_xml_saxparser.h>

#include <cassert>
#include <vector>

#include <iostream>

#include <expat.h>

namespace MvdS {
namespace a_xml {

namespace {

// --------------------
// Struct ParserContext
// --------------------

struct ParserContext
{
  XML_Parser                                        d_parser;
  kdadp::SaxDocumentHandler *                       d_documentHandler;
  std::string                                       d_data;
  std::vector<kdadp::SaxDocumentHandler::Attribute> d_attributes;
  size_t                                            d_lineNumber;
  size_t                                            d_columnNumber;

  ParserContext(XML_Parser parser)
    : d_parser(parser)
  {}

  void updateLocation()
  {
    size_t lineNumber   = XML_GetCurrentLineNumber(d_parser);
    size_t columnNumber = XML_GetCurrentColumnNumber(d_parser);

    if (lineNumber == d_lineNumber &&
	columnNumber == d_columnNumber) {
      return;
    }

    d_documentHandler->location(lineNumber, columnNumber);
    d_lineNumber   = lineNumber;
    d_columnNumber = columnNumber;
  }
  
  void parseName(const XML_Char *name)
  // Parse the specified 'name' to 'd_name'.
  {
    d_data = name;
  }

  void parseCharacterData(gsl::span<const XML_Char> data)
  // Parse the specified 'data' to 'd_data'.
  {
    d_data = std::string(data.data(), data.size());
  }

  void parseComment(const XML_Char *data)
  {
    d_data = data;
  }
  
  void parseAttributes(const XML_Char **atts)
  // Parse the specified 'atts' to 'd_attributes'.
  {
    d_attributes.clear();
    for (const XML_Char **i = atts; nullptr != *i; i += 2) {
      d_attributes.emplace_back(std::make_pair(i[0], i[1]));
    }
  }

  void startElement()
  // Call the 'startElement' handler.
  {
    d_documentHandler->startElement(d_data, d_attributes);
  }

  void characterData()
  // Call 'characterData' handler.
  {
    d_documentHandler->characterData(d_data);
  }

  void comment()
  // Call 'comment' handler.
  {
    d_documentHandler->comment(d_data);
  }
  
  void endElement()
  // Call the 'endElement' handler.
  {
    d_documentHandler->endElement(d_data);
  }


  
};

void startElement(void *userData, const XML_Char *name, const XML_Char **atts)
{  
  auto context = reinterpret_cast<ParserContext *>(userData);
  context->updateLocation();
  context->parseName(name);
  context->parseAttributes(atts);
  context->startElement();
}

void characterData(void *userData, const XML_Char *s, int len)
{
  auto context = reinterpret_cast<ParserContext *>(userData);
  context->updateLocation();
  context->parseCharacterData({s, len});
  context->characterData();
}

void comment(void *userData, const XML_Char *data)
{
  auto context = reinterpret_cast<ParserContext *>(userData);
  context->updateLocation();
  context->parseComment(data);
  context->comment();  
}

void endElement(void *userData, const XML_Char *name)
{
  auto context = reinterpret_cast<ParserContext *>(userData);
  context->updateLocation();
  context->parseName(name);
  context->endElement();
}

}; // namespace

// ----------------
// Class: SaxParser
// ----------------

// CREATORS

// MANIPULATORS
void SaxParser::setDocumentHandler(kdadp::SaxDocumentHandler *documentHandler)
{
  d_documentHandler = documentHandler;
}

bool SaxParser::parse(const gsl::span<char> &data)
{
  assert(nullptr != d_documentHandler);

  XML_Parser parser = XML_ParserCreate(NULL);
  
  ParserContext context(parser);
  context.d_documentHandler = d_documentHandler;

  XML_SetUserData(parser, &context);
  XML_SetElementHandler(parser, startElement, endElement);
  XML_SetCharacterDataHandler(parser, characterData);
  XML_SetCommentHandler(parser, comment);

  if (XML_STATUS_ERROR == XML_Parse(parser, data.data(), static_cast<int>(data.size()), true)) {
    // Log error!
    std::cerr << XML_GetCurrentLineNumber(parser) << ":error: " << XML_ErrorString(XML_GetErrorCode(parser)) << std::endl;
    return false;
  }
  
  XML_ParserFree(parser);

  return true;
}

bool SaxParser::parse(std::istream &stream)
{
  assert(nullptr != d_documentHandler);

  XML_Parser parser = XML_ParserCreate(NULL);
  
  ParserContext context(parser);
  context.d_documentHandler = d_documentHandler;

  XML_SetUserData(parser, &context);
  XML_SetElementHandler(parser, startElement, endElement);
  XML_SetCharacterDataHandler(parser, characterData);
  XML_SetCommentHandler(parser, comment);

  char buffer[1 * 1024];

  while (stream) {
    stream.read(buffer, sizeof(buffer));
    if (XML_STATUS_ERROR == XML_Parse(parser,
                                      buffer,
                                      static_cast<int>(stream.gcount()),
                                      static_cast<bool>(stream))) {
      // Log error!
      std::cerr << XML_GetCurrentLineNumber(parser) << ":error: " << XML_ErrorString(XML_GetErrorCode(parser)) << std::endl;
      return false;
    }
  }
  
  XML_ParserFree(parser);

  return true;
}

// ACCESSORS

} // namespace a_xml
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
