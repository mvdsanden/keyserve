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

  void startDocument() override {}

  void startElement(const std::string &name,
                    const Attributes & attributes) override
  {
    std::shared_ptr<kdadm::Element> element = kdadm::Element::createElement(name);

    element->attributes().insert(element->attributes().end(),
                                 std::begin(attributes),
                                 std::end(attributes));

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
    
    d_stck.top()->children().emplace_back(element);
  }

  void comment(const std::string &data) override
  {
  }

  void endElement(const std::string &name) override
  {
    assert(!d_stck.empty());
    assert(name == d_stck.top()->tag());
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
bool XmlDocumentParser::parse(kdadm::Document *document, std::istream& stream)
{
  Context          context;
  a_xml::SaxParser parser;
  parser.setDocumentHandler(&context);
  if (!parser.parse(stream)) {
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
