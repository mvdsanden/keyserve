// m_cfgen_codegenerator.cpp                                          -*-c++-*-
#include <m_cfgen_codegenerator.h>
#include <kdadm_element.h>

#include <iostream>

namespace MvdS {
namespace m_cfgen {

namespace {
  struct Context {

    std::vector<std::shared_ptr<kdadm::Element>> d_complexTypes;
    std::vector<std::shared_ptr<kdadm::Element>> d_element;

  };

  // struct ElementTypeParser;
  // struct ComplexTypeParser;

  struct ElementTypeValidator {

    Context *d_context;
    
    ElementTypeValidator(Context *context)
      : d_context(context)
    {}
    
    void operator=(const std::shared_ptr<kdadm::Element>& element)
    {
      std::cout << "Element: " << element->tag() << "\n";

      auto nameIter = kdadm::ElementUtils::getAttributeByName(
          "name", element->attributes().begin(), element->attributes().end());

      if (element->attributes().end() == nameIter) {
	std::cerr << "Element had no name.\n";
	return;
      }

      std::string name = nameIter->second;

      auto typeIter = kdadm::ElementUtils::getAttributeByName(
          "type", element->attributes().begin(), element->attributes().end());

      if (element->attributes().end() == typeIter) {
	std::cerr << "Element '" << name << "' has no type.\n";
	return;
      }

      std::string typeName = typeIter->second;

      auto actualTypeIter = std::find(typeName, d_context...
    }

    void operator++()
    {
    }
    
  };
  
  struct ComplexTypeValidator {

    Context *d_context;

    ComplexTypeValidator(Context *context)
      : d_context(context)
    {}
    
    void operator=(const std::shared_ptr<kdadm::Element>& element)
    {
      std::cout << "ComplexType: " << element->tag() << "\n";

      auto nameIter = kdadm::ElementUtils::getAttributeByName(
          "name", element->attributes().begin(), element->attributes().end());

      if (element->attributes().end() == nameIter) {
	std::cerr << "Complex type had no name.\n";
	return;
      }

      std::string typeName = nameIter->second;

      auto sequence =
          kdadm::ElementUtils::getElementByTagName("xs:sequence",
                                                   element->children().begin(),
                                                   element->children().end());

      if (element->children().end() == sequence) {
	std::cerr << "Log: no sequence in complex type: " << typeName << "\n";
	return;
      }

      ElementTypeValidator elementTypeValidator(d_context);
      (*sequence)->getElementsByTagName(&elementTypeValidator, "xs:element");

      d_context->d_complexTypes.emplace_back(element);
    }

    void operator++()
    {
    }
    
  };

  
  bool parseDocument(Context *context, const kdadm::Document& document)
  {

    std::shared_ptr<kdadm::Element> root = document.root();
    if (!root) {
      return false;
    }

    // for (auto child : root->children()) {
    //   std::cout << "- " << (child->isElementType()?child->tag():child->value()) << ".\n";
    // }
    
    ComplexTypeValidator complexTypeValidator(context);
    ElementTypeValidator elementTypeValidator(context);
    
    root->getElementsByTagName(&complexTypeValidator, "xs:complexType");
    root->getElementsByTagName(&elementTypeValidator, "xs:element");

    return true;
  }
  
}; // anonymous namespace

// --------------------
// Class: CodeGenerator
// --------------------

// CREATORS
CodeGenerator::CodeGenerator(const CommandlineArgs &arguments)
{
}

// MANIPULATORS
bool CodeGenerator::generate(std::ostream &stream, const kdadm::Document& document)
{
  Context context;
  if (!parseDocument(&context, document)) {
    return false;
  }

  // printHeader(stream, context);

  // printForwardDeclarations(stream, context));

  // printTypeDefinitions(stream, context);

  return static_cast<bool>(stream);
}

// MANIPULATORS

// ACCESSORS

} // namespace m_cfgen
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
