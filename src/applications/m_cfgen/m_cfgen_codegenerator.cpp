// m_cfgen_codegenerator.cpp                                          -*-c++-*-
#include <m_cfgen_codegenerator.h>
#include <kdadm_element.h>

#include <iostream>
#include <unordered_map>

namespace MvdS {
namespace m_cfgen {

namespace {
  struct Context {

    std::unordered_map<std::string, std::shared_ptr<kdadm::Element>> d_complexTypes;
    std::vector<std::shared_ptr<kdadm::Element>> d_element;

    

  };

  struct ElementTypeValidator {

    Context *d_context;
    
    ElementTypeValidator(Context *context)
      : d_context(context)
    {}
    
    void operator=(std::shared_ptr<kdadm::Element> element)
    {
      auto nameIter = kdadm::ElementUtils::getAttributeByName(
          "name", element->attributes().begin(), element->attributes().end());

      if (element->attributes().end() == nameIter) {
	std::cerr << element->location() << " element has no name.\n";
	return;
      }

      std::string name = nameIter->second;

      auto typeIter = kdadm::ElementUtils::getAttributeByName(
          "type", element->attributes().begin(), element->attributes().end());

      if (element->attributes().end() == typeIter) {
	std::cerr << element->location() << " element '" << name << "' has no type.\n";
	return;
      }

      std::string typeName = typeIter->second;

      auto actualTypeIter = d_context->d_complexTypes.find(typeName);

      if (d_context->d_complexTypes.end() == actualTypeIter) {
	std::cerr << element->location() << "Unknown type: " << typeName << "\n";
	return;
      }

      element->children().push_back(actualTypeIter->second);
    }

    ElementTypeValidator& operator*() { return *this; }
    
    void operator++()
    {
    }
    
  };
  
  struct ComplexTypeValidator {

    Context *d_context;

    ComplexTypeValidator(Context *context)
      : d_context(context)
    {}
    
    void operator=(std::shared_ptr<kdadm::Element> element)
    {
      auto nameIter = kdadm::ElementUtils::getAttributeByName(
          "name", element->attributes().begin(), element->attributes().end());

      if (element->attributes().end() == nameIter) {
	std::cerr << element->location() << " complex type had no name.\n";
	return;
      }

      std::string typeName = nameIter->second;

      auto sequenceIter =
          kdadm::ElementUtils::getElementByTagName("xs:sequence",
                                                   element->children().begin(),
                                                   element->children().end());

      if (element->children().end() == sequenceIter) {
	std::cerr << element->location() << " no sequence in complex type: " << typeName << "\n";
	return;
      }

      auto sequence = *sequenceIter;
      
      ElementTypeValidator elementTypeValidator(d_context);
      sequence->getElementsByTagName(elementTypeValidator, "xs:element");

      if (d_context->d_complexTypes.find(typeName) != d_context->d_complexTypes.end()) {
	std::cerr << element->location() << " type already defined: " << typeName << "\n";
      }
      
      d_context->d_complexTypes.emplace(typeName, element);
    }

    void operator++()
    {
    }

    ComplexTypeValidator& operator*() { return *this; }
    
  };

  struct InternalTypeValidator {

    Context *d_context;

    InternalTypeValidator(Context *context)
      : d_context(context)
    {}
    
    void operator=(std::shared_ptr<kdadm::Element> element)
    {
      auto nameIter = kdadm::ElementUtils::getAttributeByName(
          "name", element->attributes().begin(), element->attributes().end());

      if (element->attributes().end() == nameIter) {
	std::cerr << element->location() << " internal type has no name.\n";
	return;
      }

      std::string typeName = nameIter->second;

      d_context->d_complexTypes.insert(std::make_pair(typeName, element));
    }

    void operator++()
    {
    }

    InternalTypeValidator& operator*() { return *this; }
    
  };

  
  bool parseDocument(Context *context, const kdadm::Document& document)
  {

    std::shared_ptr<kdadm::Element> root = document.root();
    if (!root) {
      return false;
    }

    InternalTypeValidator internalTypeValidator(context);
    ComplexTypeValidator complexTypeValidator(context);
    ElementTypeValidator elementTypeValidator(context);
    
    root->getElementsByTagName(internalTypeValidator, "xs:internalType");
    root->getElementsByTagName(complexTypeValidator, "xs:complexType");
    root->getElementsByTagName(elementTypeValidator, "xs:element");

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
