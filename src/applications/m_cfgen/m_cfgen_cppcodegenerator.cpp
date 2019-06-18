// m_cfgen_cppcodegenerator.cpp                                       -*-c++-*-
#include <kdadm_document.h>
#include <kdadm_element.h>
#include <m_cfgen_commandlineargs.h>
#include <m_cfgen_cppcodegenerator.h>

#include <algorithm>
#include <cassert>
#include <string>
#include <fstream>
#include <iostream>

namespace MvdS {
namespace m_cfgen {

namespace {

std::shared_ptr<kdadm::Element>
cppFromInternal(const std::shared_ptr<kdadm::Element> &typeElement)
{
  auto cppIter = kdadm::ElementUtils::getElementByTagName(
      "cpp", typeElement->children().begin(), typeElement->children().end());
  return (cppIter != typeElement->children().end()?*cppIter:nullptr);
}

bool cppTypeName(std::string *                          typeName,
                 const std::shared_ptr<kdadm::Element> &cpp)
{
  auto typeIter = kdadm::ElementUtils::getAttributeByName(
      "type", cpp->attributes().begin(), cpp->attributes().end());

  if (cpp->attributes().end() == typeIter) {
    std::cerr << cpp->location() << " expected 'type' attribute.\n";
    return false;
  }

  *typeName = typeIter->second;
  
  return true;
}

std::string extractAttribute(const std::string &                    name,
                             const std::shared_ptr<kdadm::Element> &element)
{
  auto iter = kdadm::ElementUtils::getAttributeByName(
      name, element->attributes().begin(), element->attributes().end());
  assert(element->attributes().end() != iter);
  return iter->second;
}

std::shared_ptr<kdadm::Element>
extractElement(const std::string &                    name,
               const std::shared_ptr<kdadm::Element> &element)
{
  auto iter = kdadm::ElementUtils::getElementByTagName(
      name, element->children().begin(), element->children().end());
  assert(element->children().end() != iter);
  return *iter;
  }

void extractOccurs(size_t *                               minOccurs,
                   size_t *                               maxOccurs,
                   const std::shared_ptr<kdadm::Element> &element)
{
  assert(minOccurs);
  assert(maxOccurs);
  
  auto minOccursIter = kdadm::ElementUtils::getAttributeByName(
      "minOccurs", element->attributes().begin(), element->attributes().end());

  *minOccurs = (element->attributes().end() == minOccursIter
                   ? *minOccurs
                   : std::stoi(minOccursIter->second));

  auto maxOccursIter = kdadm::ElementUtils::getAttributeByName(
      "maxOccurs", element->attributes().begin(), element->attributes().end());

  *maxOccurs = (element->attributes().end() == maxOccursIter
                   ? *maxOccurs
                   : std::stoi(maxOccursIter->second));
}

std::string
modifyTypeForOccurs(std::string type, size_t minOccurs, size_t maxOccurs)
{
  if (1 < maxOccurs) {
    type = "std::vector<" + type + ">";
  } else if (0 == minOccurs) {
    type = "std::optional<" + type + ">";
  }

  return std::move(type);
}

void generateClassBanner(std::ostream &stream, const std::string &name)
{
  stream << "// " << std::string(name.size() + 6, '-') << "\n";
  stream << "// class " << name << "\n";
  stream << "// " << std::string(name.size() + 6, '-') << "\n";
}

bool generateVariableDefinition(
    std::ostream &                         stream,
    std::string                            type,
    const std::string &                    name,
    size_t                                 minOccurs,
    size_t                                 maxOccurs,
    const std::shared_ptr<kdadm::Element> &typeElement)
{
  if ("xs:internalType" == typeElement->tag()) {
    auto cpp = cppFromInternal(typeElement);
    if (!cpp) {
      std::cerr << typeElement->location()
                << " no 'cpp' specification for internal type.\n";
      return false;
    }

    cppTypeName(&type, cpp);
  }

  type = modifyTypeForOccurs(type, minOccurs, maxOccurs);
  
  stream << type << " d_" << name << ";\n";
  return true;
}

bool generateAccessorDefinition(
    std::ostream &                         stream,
    std::string                            type,
    const std::string &                    name,
    size_t                                 minOccurs,
    size_t                                 maxOccurs,
    const std::shared_ptr<kdadm::Element> &typeElement)
{
  if ("xs:internalType" == typeElement->tag()) {
    auto cpp = cppFromInternal(typeElement);
    if (!cpp) {
      std::cerr << typeElement->location()
                << " no 'cpp' specification for internal type.\n";
      return false;
    }

    cppTypeName(&type, cpp);
  }

  type = modifyTypeForOccurs(type, minOccurs, maxOccurs);
  
  stream << "const " << type << "& " << name << "() const;\n";
  return true;
}

bool generateManipulatorDefinition(
    std::ostream &                         stream,
    std::string                            type,
    const std::string &                    name,
    size_t                                 minOccurs,
    size_t                                 maxOccurs,
    const std::shared_ptr<kdadm::Element> &typeElement)
{
  if ("xs:internalType" == typeElement->tag()) {
    auto cpp = cppFromInternal(typeElement);
    if (!cpp) {
      std::cerr << typeElement->location()
                << " no 'cpp' specification for internal type.\n";
      return false;
    }

    cppTypeName(&type, cpp);
  }

  type = modifyTypeForOccurs(type, minOccurs, maxOccurs);  
  stream << type << "& " << name << "();\n";

  return true;
}

bool generateStreamSpecification(
    std::ostream &                         stream,
    std::string                            type,
    const std::string &                    name,
    size_t                                 minOccurs,
    size_t                                 maxOccurs,
    const std::shared_ptr<kdadm::Element> &typeElement)
{
  if ("xs:internalType" == typeElement->tag()) {
    auto cpp = cppFromInternal(typeElement);
    if (!cpp) {
      std::cerr << typeElement->location()
                << " no 'cpp' specification for internal type.\n";
      return false;
    }

    cppTypeName(&type, cpp);
  }

  type = modifyTypeForOccurs(type, minOccurs, maxOccurs);

  // TODO: implement!

  return true;
}

  
struct Context
{

  std::shared_ptr<kdadm::Element> d_root;
  std::string                     d_enterpriseNs;
  std::string                     d_ns;
  std::string                     d_name;

  struct VariableDefinitionGenerator
  {
    // PUBLIC DATA
    std::ostream &d_stream;
    Context *     d_context;

    // CREATORS
    VariableDefinitionGenerator(std::ostream &stream, Context *context)
        : d_stream(stream)
        , d_context(context)
    {
      d_stream << "// DATA\n";
    }

    // MANIPULATORS
    VariableDefinitionGenerator &operator*() { return *this; }

    void operator++() {}

    void operator=(std::shared_ptr<kdadm::Element> element)
    {
      std::string name = extractAttribute("name", element);
      std::string type = extractAttribute("type", element);

      size_t minOccurs = 1;
      size_t maxOccurs = 1;

      extractOccurs(&minOccurs, &maxOccurs, element);

      assert(1 == element->children().size());

      generateVariableDefinition(
          d_stream, type, name, minOccurs, maxOccurs, element->children()[0]);
    }
  };

  struct AccessorDefinitionGenerator
  {
    // PUBLIC DATA
    std::ostream &d_stream;
    Context *     d_context;

    // CREATORS
    AccessorDefinitionGenerator(std::ostream &stream, Context *context)
        : d_stream(stream)
        , d_context(context)
    {
      d_stream << "// ACCESSORS\n";
    }

    // MANIPULATORS
    AccessorDefinitionGenerator &operator*() { return *this; }

    void operator++() {}

    void operator=(std::shared_ptr<kdadm::Element> element)
    {
      std::string name = extractAttribute("name", element);
      std::string type = extractAttribute("type", element);

      size_t minOccurs = 1;
      size_t maxOccurs = 1;

      extractOccurs(&minOccurs, &maxOccurs, element);
      
      assert(1 == element->children().size());

      generateAccessorDefinition(
          d_stream, type, name, minOccurs, maxOccurs, element->children()[0]);
    }
  };

  struct ManipulatorDefinitionGenerator
  {
    // PUBLIC DATA
    std::ostream &d_stream;
    Context *     d_context;

    // CREATORS
    ManipulatorDefinitionGenerator(std::ostream &stream, Context *context)
        : d_stream(stream)
        , d_context(context)
    {
      d_stream << "// MANIPULATOR\n";
    }

    // MANIPULATORS
    ManipulatorDefinitionGenerator &operator*() { return *this; }

    void operator++() {}

    void operator=(std::shared_ptr<kdadm::Element> element)
    {
      std::string name = extractAttribute("name", element);
      std::string type = extractAttribute("type", element);

      size_t minOccurs = 1;
      size_t maxOccurs = 1;

      extractOccurs(&minOccurs, &maxOccurs, element);
      
      assert(1 == element->children().size());

      generateManipulatorDefinition(
          d_stream, type, name, minOccurs, maxOccurs, element->children()[0]);
    }
  };

  struct StreamSpecificationGenerator
  {
    // PUBLIC DATA
    std::ostream &d_stream;
    Context *     d_context;

    // CREATORS
    StreamSpecificationGenerator(std::ostream &     stream,
                                 Context *          context,
                                 const std::string &className)
        : d_stream(stream)
        , d_context(context)
    {
      d_stream << "inline void operator>>(const kdadm::Element &element, "
               << className << "& obj)\n{\n";
    }

    ~StreamSpecificationGenerator()
    {
      d_stream << "}\n";
    }
    
    // MANIPULATORS
    StreamSpecificationGenerator &operator*() { return *this; }

    void operator++() {}

    void operator=(std::shared_ptr<kdadm::Element> element)
    {
      std::string name = extractAttribute("name", element);
      std::string type = extractAttribute("type", element);

      size_t minOccurs = 1;
      size_t maxOccurs = 1;

      extractOccurs(&minOccurs, &maxOccurs, element);
      
      assert(1 == element->children().size());

      generateStreamSpecification(
          d_stream, type, name, minOccurs, maxOccurs, element->children()[0]);
    }
  };

  
  struct TypeDefinitionGenerator
  {
    // PUBLIC DATA
    std::ostream &d_stream;
    Context *     d_context;

    // CREATORS
    TypeDefinitionGenerator(std::ostream &stream, Context *context)
        : d_stream(stream)
        , d_context(context)
    {}

    // MANIPULATORS
    TypeDefinitionGenerator &operator*() { return *this; }

    void operator++() {}

    void operator=(std::shared_ptr<kdadm::Element> element)
    {
      std::string name     = extractAttribute("name", element);
      auto        sequence = extractElement("xs:sequence", element);

      generateClassBanner(d_stream, name);
      d_stream << "class " << name << "\n"
               << "{\n";

      VariableDefinitionGenerator variableDefinitionGenerator(d_stream,
                                                              d_context);
      sequence->getElementsByTagName(variableDefinitionGenerator, "xs:element");

      d_stream << "public:\n"
	       << "// CREATORS\n";

      ManipulatorDefinitionGenerator manipulatorDefinitionGenerator(d_stream,
                                                                    d_context);
      sequence->getElementsByTagName(manipulatorDefinitionGenerator, "xs:element");


      AccessorDefinitionGenerator accessorDefinitionGenerator(d_stream,
                                                              d_context);
      sequence->getElementsByTagName(accessorDefinitionGenerator, "xs:element");
      
      d_stream << "}; // class " << name << "\n";

      d_stream << "// --- inline methods ---\n";

      StreamSpecificationGenerator streamSpecificationGenerator(
          d_stream, d_context, name);
      sequence->getElementsByTagName(streamSpecificationGenerator,
                                     "xs:element");

      
    }
  };

  void beginDocument(std::ostream &stream, const std::string &filename)
  {
    stream << "// " << filename << std::string(80 - filename.size() - 13, ' ')
           << "-*-c++-*-\n";
  }

  void beginNamespaces(std::ostream &stream)
  {
    stream << "namespace " << d_enterpriseNs << " {\n";
    stream << "namespace " << d_ns << " {\n";
  }

  void endNamespaces(std::ostream &stream)
  {
    stream << "}; // namespace " << d_ns << "\n";
    stream << "}; // namespace " << d_enterpriseNs << "\n";
  }

  bool generateHeader()
  {
    std::string lcNs   = d_ns;
    std::string lcName = d_name;

    std::transform(lcNs.begin(), lcNs.end(), lcNs.begin(), ::tolower);
    std::transform(lcName.begin(), lcName.end(), lcName.begin(), ::tolower);

    std::string filename = lcNs + "_" + lcName + ".h";

    std::ofstream stream(filename);
    if (!stream) {
      std::cerr << "Error opening header file: '" << filename << "'.\n";
      return false;
    }

    beginDocument(stream, filename);

    beginNamespaces(stream);

    TypeDefinitionGenerator typeGenerator(stream, this);
    d_root->getElementsByTagName(typeGenerator, "xs:complexType");

    endNamespaces(stream);

    return static_cast<bool>(stream);
  }
};
}; // anonymous namespace

// -----------------------
// Class: CppCodeGenerator
// -----------------------

// CREATORS
CppCodeGenerator::CppCodeGenerator(const CommandlineArgs &arguments) {}

// MANIPULATORS
bool CppCodeGenerator::generate(const kdadm::Document &document)
{
  auto root = document.root();
  assert(root);

  auto name = kdadm::ElementUtils::getAttributeByName(
      "name", root->attributes().begin(), root->attributes().end());
  assert(root->attributes().end() != name);

  auto ns = kdadm::ElementUtils::getAttributeByName(
      "ns", root->attributes().begin(), root->attributes().end());
  assert(root->attributes().end() != ns);

  auto enterpriseNs = kdadm::ElementUtils::getAttributeByName(
      "enterpriseNs", root->attributes().begin(), root->attributes().end());
  assert(root->attributes().end() != enterpriseNs);

  Context context;
  context.d_root         = root;
  context.d_enterpriseNs = enterpriseNs->second;
  context.d_ns           = ns->second;
  context.d_name         = name->second;

  if (!context.generateHeader()) {
    return false;
  }

  return true;
}

// ACCESSORS

} // namespace m_cfgen
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
