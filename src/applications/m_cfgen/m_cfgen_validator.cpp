// m_cfgen_validator.cpp                                          -*-c++-*-
#include <kdadm_element.h>
#include <m_cfgen_validator.h>

#include <iostream>
#include <set>
#include <unordered_map>

namespace MvdS {
namespace m_cfgen {

namespace {

std::pair<std::string, std::shared_ptr<kdadm::Element>>
internalType(const std::string &name,
             const std::string &cppName,
             const std::string &cppInclude)
{
  auto root = kdadm::Element::createElement("xs:internalType");
  root->attributes().emplace_back("name", name);

  auto cpp =
      root->children().emplace_back(kdadm::Element::createElement("xs:cpp"));
  cpp->attributes().emplace_back("type", cppName);
  cpp->attributes().emplace_back("include", cppInclude);
  
  return std::make_pair(name, std::move(root));
}

// ------------------------
// Struct ValidationContext
// ------------------------
struct ValidationContext
{
  // PUBLIC TYPES
  typedef std::unordered_map<std::string, std::shared_ptr<kdadm::Element>>
                                   ComplexTypes;

  // PUBLIC DATA
  ComplexTypes                               d_complexTypes;
  bool                                       d_success = true;
  std::set<std::shared_ptr<kdadm::Element>>  d_usedInternalTypes;

  // CREATORS
  ValidationContext()
  {
    d_complexTypes.insert(internalType("xs:string", "std::string", "string"));
  }
  
  // MANIPULATORS
  std::shared_ptr<kdadm::Element> resolveType(const std::string &typeName)
  // Resolve the specified 'typeName' into an element representing the type.
  // Return 'NULL' when not found.
  {
    auto iter = d_complexTypes.find(typeName);
    if (d_complexTypes.end() == iter) {
      return nullptr;
    }

    if ("xs:internalType" == iter->second->tag()) {
      d_usedInternalTypes.emplace(iter->second);
    }

    return iter->second;
  }

  bool registerType(const std::string &                    typeName,
                    const std::shared_ptr<kdadm::Element> &element)
  // Register the specified 'element' under the specified 'typeName'. Return
  // 'false' if there already is a type registered under 'typeName'.
  {
    if (d_complexTypes.find(typeName) != d_complexTypes.end()) {
      std::cerr << element->location() << " type already defined: " << typeName
                << "\n";
      return false;
    }
    d_complexTypes.emplace(typeName, element);
    return true;
  }
};

bool expectAttribute(std::string *                          value,
                     const std::string &                    name,
                     const std::shared_ptr<kdadm::Element> &element)
// Expect an attribute with the specified 'name' in the specified 'element. If
// found store the value into the specified 'value'. Return 'false' if not
// found.
{
  auto iter = kdadm::ElementUtils::getAttributeByName(
      name, element->attributes().begin(), element->attributes().end());

  if (element->attributes().end() == iter) {
    std::cerr << element->location() << " expected element to have attribute: '"
              << name << "'.\n";
    return false;
  }

  *value = iter->second;
  return true;
}

std::shared_ptr<kdadm::Element>
expectElementWithTagName(const std::string &                    name,
                         const std::shared_ptr<kdadm::Element> &element)
// Expect a child with the specified 'name' in the specified 'element. Return a
// reference to the child if found, otherwise return 'NULL'.
{
  auto iter = kdadm::ElementUtils::getElementByTagName(
      name, element->children().begin(), element->children().end());

  if (element->children().end() == iter) {
    std::cerr << element->location() << " expected child with tag: '" << name
              << "'.\n";
    return nullptr;
  }

  return *iter;
}

// -----------------------
// Struct ElementValidator
// -----------------------

struct ElementValidator
{
  // PUBLIC DATA
  ValidationContext *d_context;

  // CREATORS
  ElementValidator(ValidationContext *context)
      : d_context(context)
  {}

  void operator()(std::shared_ptr<kdadm::Element> element)
  {
    std::string name;
    if (!expectAttribute(&name, "name", element)) {
      d_context->d_success = false;
      return;
    }

    std::string typeName;
    if (!expectAttribute(&typeName, "type", element)) {
      d_context->d_success = false;
      return;
    }

    auto typeElement = d_context->resolveType(typeName);
    if (!typeElement) {
      std::cerr << element->location() << " unknown type: '" << typeName
                << "'\n";
      d_context->d_success = false;
      return;
    }

    element->children().emplace_back(std::move(typeElement));
  }
};

// ---------------------------
// Struct ComplexTypeValidator
// ---------------------------

struct ComplexTypeValidator
{
  // PUBLIC DATA
  ValidationContext *d_context;

  // CREATORS
  ComplexTypeValidator(ValidationContext *context)
      : d_context(context)
  {}

  // MANIPULATORS
  void operator()(std::shared_ptr<kdadm::Element> element)
  {
    std::string typeName;
    if (!expectAttribute(&typeName, "name", element)) {
      d_context->d_success = false;
      return;
    }

    std::shared_ptr<kdadm::Element> sequence =
        expectElementWithTagName("xs:sequence", element);
    if (!sequence) {
      d_context->d_success = false;
      return;
    }

    ElementValidator elementTypeValidator(d_context);
    sequence->getElementsByTagName("xs:element", std::ref(elementTypeValidator));

    if (!d_context->registerType(typeName, element)) {
      d_context->d_success = false;
      return;
    }
  }
};

// ----------------------------
// Struct InternalTypeValidator
// ----------------------------

struct InternalTypeValidator
{
  // PUBLIC DATA
  ValidationContext *d_context;

  // CREATORS
  InternalTypeValidator(ValidationContext *context)
      : d_context(context)
  {}

  // MANIPULATORS
  void operator()(std::shared_ptr<kdadm::Element> element)
  {
    std::string typeName;
    if (!expectAttribute(&typeName, "name", element)) {
      d_context->d_success = false;
      return;
    }

    if (!d_context->registerType(typeName, element)) {
      d_context->d_success = false;
      return;
    }
  }
};
}; // anonymous namespace

// ----------------
// Class: Validator
// ----------------

// CREATORS
Validator::Validator(const CommandlineArgs &arguments) {}

// MANIPULATORS
bool Validator::validate(kdadm::Document *document)
{
  std::shared_ptr<kdadm::Element> root = document->root();
  if (!root) {
    // Empty document.
    return true;
  }

  ValidationContext context;

  std::string name;
  if (!expectAttribute(&name, "name", root)) {    
    context.d_success = false;
  }

  std::string ns;
  if (!expectAttribute(&ns, "ns", root)) {
    context.d_success = false;
  }

  std::string enterpriseNs;
  if (!expectAttribute(&enterpriseNs, "enterpriseNs", root)) {
    context.d_success = false;
  }
  
  InternalTypeValidator internalTypeValidator(&context);
  ComplexTypeValidator  complexTypeValidator(&context);
  ElementValidator      elementTypeValidator(&context);

  root->getElementsByTagName("xs:internalType", std::ref(internalTypeValidator));
  root->getElementsByTagName("xs:complexType", std::ref(complexTypeValidator));
  root->getElementsByTagName("xs:element", std::ref(elementTypeValidator));

  for (const auto& internalType : context.d_usedInternalTypes) {
    root->children().emplace_back(internalType);
  }
  
  return context.d_success;
}

// ACCESSORS

} // namespace m_cfgen
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
