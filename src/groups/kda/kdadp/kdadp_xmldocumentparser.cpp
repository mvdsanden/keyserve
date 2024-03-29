// kdadp_xmldocumentparser.cpp                                        -*-c++-*-
#include <kdadp_xmldocumentparser.h>

#include <a_xml_saxparser.h>

#include <kdadm_element.h>
#include <kdadm_document.h>

#include <cassert>
#include <stack>

namespace MvdS {
namespace kdadp {

namespace {

struct Context : public kdadp::SaxDocumentHandler
{
  std::shared_ptr<kdadm::Element>             d_root;
  std::stack<std::shared_ptr<kdadm::Element>> d_stck;
  std::shared_ptr<std::string>                d_sourceName;
  size_t                                      d_lineNumber;
  size_t                                      d_columnNumber;

  void location(const std::shared_ptr<std::string> &sourceName,
                size_t                              lineNumber,
                size_t                              columnNumber) override
  {
    d_sourceName   = sourceName;
    d_lineNumber   = lineNumber;
    d_columnNumber = columnNumber;
  }
  
  void startDocument() override {}

  void startElement(const std::string &name,
                    const Attributes & attributes) override
  {
    std::shared_ptr<kdadm::Element> element = kdadm::Element::createElement(name);

    element->attributes().insert(element->attributes().end(),
                                 std::begin(attributes),
                                 std::end(attributes));

    element->location().d_sourceName    = d_sourceName;
    element->location().d_lineNumbers   = {d_lineNumber, d_lineNumber};
    element->location().d_columnNumbers = {d_columnNumber, d_columnNumber};

    if (!d_root) {
      d_root = element;
    } else {
      assert(!d_stck.empty());
      d_stck.top()->children().emplace_back(element);
    }
    
    d_stck.push(element);
  }

  void characterData(const std::string &data) override
  {
    if (d_stck.empty()) {
      return;
    }

    // Append to back if it was a value element.
    if (!d_stck.top()->children().empty()
	&& d_stck.top()->children().back()->isValueType()) {
      d_stck.top()->children().back()->setValue(
          d_stck.top()->children().back()->value() + data);
      return;
    }
    
    std::shared_ptr<kdadm::Element> element = kdadm::Element::createValue(data);

    element->location().d_sourceName    = d_sourceName;
    element->location().d_lineNumbers   = {d_lineNumber, d_lineNumber};
    element->location().d_columnNumbers = {d_columnNumber, d_columnNumber};

    d_stck.top()->children().emplace_back(element);
  }

  void comment(const std::string &data) override
  {
  }

  void endElement(const std::string &name) override
  {
    assert(!d_stck.empty());
    assert(name == d_stck.top()->tag());
    d_stck.top()->location().d_lineNumbers.second   = d_lineNumber;
    d_stck.top()->location().d_columnNumbers.second = d_columnNumber;
    d_stck.pop();
  }

  void endDocument() override {}
};

}; // anonymous namespace

// ------------------------
// Class: XmlDocumentParser
// ------------------------

// CREATORS
XmlDocumentParser::XmlDocumentParser() {}

// MANIPULATORS
bool XmlDocumentParser::parse(kdadm::Document *  document,
                              std::istream &     stream,
                              const std::string &sourceName)
{
  Context          context;
  a_xml::SaxParser parser;
  parser.setDocumentHandler(&context);
  if (!parser.parse(stream, sourceName)) {
    return false;
  }

  document->setRoot(context.d_root);
  return true;
}

// ACCESSORS

} // namespace kdadp
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
