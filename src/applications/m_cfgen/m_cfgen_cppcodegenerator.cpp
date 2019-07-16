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
#include <set>
#include <optional>

namespace MvdS {
namespace m_cfgen {

namespace {

std::shared_ptr<kdadm::Element>
tryExtractElement(const std::string &                    tagName,
                  const std::shared_ptr<kdadm::Element> &element)
// Try to extract a child with the specified 'tagName' from the specified
// 'element'. Return the child element or NULL when it does not exist.
{
  auto iter = kdadm::ElementUtils::getElementByTagName(
      tagName, element->children().begin(), element->children().end());
  return (element->children().end() != iter?*iter:nullptr);
}
  
std::shared_ptr<kdadm::Element>
extractElement(const std::string &                    tagName,
               const std::shared_ptr<kdadm::Element> &element)
// Extract a child with the specified 'tagName' from the specified 'element'.
// Return the child element. Behavior is undefined unless there exists at least
// one element with 'tagName' in 'element'.
{
  auto result = tryExtractElement(tagName, element);
  assert(result);
  return result;
}

std::optional<std::string>
tryExtractAttribute(const std::string &                    name,
                    const std::shared_ptr<kdadm::Element> &element)
// Try to extract an attribute with the specified 'name' from the specified
// 'element'. Return the value as an optional.
{
  auto iter = kdadm::ElementUtils::getAttributeByName(
      name, element->attributes().begin(), element->attributes().end());
  if (element->attributes().end() == iter) {
    return std::nullopt;
  }
  
  return iter->second;
}

std::optional<long long>
tryExtractIntegerAttribute(const std::string &                    name,
                           const std::shared_ptr<kdadm::Element> &element)
// Try to extract an integer attribute with the specified 'name' from the
// specified 'element'. Return the value as an optional.
{
  auto value = tryExtractAttribute(name, element);
  if (!value) {
    return std::nullopt;
  }

  return std::stoll(*value);
}

  
std::string extractAttribute(const std::string &                    name,
                             const std::shared_ptr<kdadm::Element> &element)
// Extract an attribute with the specified 'name' from the specified
// 'element'. Return the value. Behavior is undefined unless an attribute with
// 'name' exists.
{
  auto result = tryExtractAttribute(name, element);
  assert(result);
  return *result;;
}
  
std::shared_ptr<kdadm::Element>
cppFromInternal(const std::shared_ptr<kdadm::Element> &typeElement)
// Try to extract a child the 'xs:cpp' tag name from the specified
// 'typeElement'. Return the child element or NULL when it does not exist.
{
  return tryExtractElement("xs:cpp", typeElement);
}

std::optional<std::string>
cppTypeName(const std::shared_ptr<kdadm::Element> &cpp)
// Try to extract the internal type name from the specified 'cpp' element.
// Return an optional value.
{
  auto type = tryExtractAttribute("type", cpp);

  if (!cpp) {
    std::cerr << cpp->location() << " expected 'type' attribute.\n";
  }

  return std::move(type);
}

std::optional<std::string>
internalTypeName(const std::shared_ptr<kdadm::Element> &typeElement)
// Return the internal type name if the specified 'typeElement' is an internal
// type, return 'std::nullopt' otherwise.
{
  if ("xs:internalType" != typeElement->tag()) {
    return std::nullopt;
  }

  auto cpp = cppFromInternal(typeElement);
  if (!cpp) {
    std::cerr << typeElement->location()
              << " no 'cpp' specification for internal type.\n";
    return std::nullopt;
  }

  return std::move(cppTypeName(cpp));
}

std::string typeQuoted(const std::shared_ptr<kdadm::Element> &typeElement,
                       const std::string &                    value)
{
  auto cpp = cppFromInternal(typeElement);
  if (!cpp) {
    return value;
  }

  auto quoteChar = tryExtractAttribute("quote", cpp);
  if (!quoteChar) {
    return value;
  }

  return quoteChar.value() + value + quoteChar.value();
}
   
  
void extractOccurs(size_t *                               minOccurs,
                   size_t *                               maxOccurs,
                   const std::shared_ptr<kdadm::Element> &element)
// Extract the occurs attributes from the specified 'element' and store them
// into the specified 'minOccurs' and the specified 'maxOccurs'.
{
  assert(minOccurs);
  assert(maxOccurs);

  *minOccurs =
      tryExtractIntegerAttribute("minOccurs", element).value_or(*minOccurs);

  *maxOccurs =
      tryExtractIntegerAttribute("maxOccurs", element).value_or(*maxOccurs);
}

std::string
modifyTypeForOccurs(std::string type, size_t minOccurs, size_t maxOccurs)
// Modify the specified 'type' so that it complies with the specified
// 'minOccurs' and the specified 'maxOccurs'. Return the modified type.
{
  if (1 < maxOccurs) {
    type = "std::vector<" + type + ">";
  } else if (0 == minOccurs) {
    type = "std::optional<" + type + ">";
  }

  return std::move(type);
}

void generateClassBanner(std::ostream &stream, const std::string &name)
// Print a class banner with the specified 'name' to the specified 'stream'.
{
  stream << "// " << std::string(name.size() + 6, '-') << "\n";
  stream << "// class " << name << "\n";
  stream << "// " << std::string(name.size() + 6, '-') << "\n";
}

bool generateMemberVariableDefinition(
    std::ostream &                         stream,
    std::string                            type,
    const std::string &                    name,
    size_t                                 minOccurs,
    size_t                                 maxOccurs,
    const std::shared_ptr<kdadm::Element> &typeElement,
    const std::optional<std::string> &     value)
// Print a member variable definition with the specified 'type', the specified
// 'name' for the specified 'minOccurs' and the specified 'maxOccurs' having the
// specified 'typeElement' to the specified 'stream'.
{
  type = internalTypeName(typeElement).value_or(type);
  type = modifyTypeForOccurs(type, minOccurs, maxOccurs);
  
  stream << type << " d_" << name;

  if (value) {
    stream << " = " << typeQuoted(typeElement, value.value());
  }

  stream << ";\n";
  
  return true;
}

bool generateAccessorDefinition(
    std::ostream &                         stream,
    std::string                            type,
    const std::string &                    name,
    size_t                                 minOccurs,
    size_t                                 maxOccurs,
    const std::shared_ptr<kdadm::Element> &typeElement)
// Print a accessor definition with the specified 'type', the specified
// 'name' for the specified 'minOccurs' and the specified 'maxOccurs' having the
// specified 'typeElement' to the specified 'stream'.
{
  type = internalTypeName(typeElement).value_or(type);
  type = modifyTypeForOccurs(type, minOccurs, maxOccurs);  
  stream << "const " << type << "& " << name << "() const { return d_" << name << ";}\n";
  return true;
}

bool generateManipulatorDefinition(
    std::ostream &                         stream,
    std::string                            type,
    const std::string &                    name,
    size_t                                 minOccurs,
    size_t                                 maxOccurs,
    const std::shared_ptr<kdadm::Element> &typeElement)
// Print a manipulator definition with the specified 'type', the specified
// 'name' for the specified 'minOccurs' and the specified 'maxOccurs' having the
// specified 'typeElement' to the specified 'stream'.
{
  type = internalTypeName(typeElement).value_or(type);
  type = modifyTypeForOccurs(type, minOccurs, maxOccurs);  
  stream << type << "& " << name << "() { return d_" << name << ";}\n";
  return true;
}

void generateStreamParseManditory(std::ostream &     stream,
                                  const std::string &name,
                                  const std::string &type)
// Print stream parsing code for a mandatory element with the specified 'name'
// and the specified 'type' to the specified 'stream'.
{
  stream << "  { // BEGIN " << name << "\n"
         << "    auto iter = kdadm::ElementUtils::getElementByTagName(\n"
         << "      \"" << name << "\",\n"
         << "      element.children().begin(),\n"
         << "      element.children().end());\n\n"
         << "    if (iter == element.children().end()) {\n"
	 << "      spdlog::error(\"{}: expected element '{}'\",\n"
	 << "        element.location(), \"" << name << "\");\n"
	 << "      return false;\n"
	 << "    }\n\n"
	 << "    if (!(**iter >> obj." << name << "())) {\n"
	 << "      spdlog::error(\"{}: expected " << type <<" value\", (*iter)->location());\n"
	 << "      return false;\n"
	 << "    }\n"
	 << "  } // END " << name << "\n\n";
}

void generateStreamParseVector(std::ostream &     stream,
                               const std::string &name,
                               const std::string &type,
                               size_t             minOccurs)
// Print stream parsing code for a multiple occurrence element with the specified
// 'name' and the specified 'type' to the specified 'stream'.
{

  stream << "  { // BEGIN " << name << "\n"
         << "    bool success = true;\n"
         << "    element.getElementsByTagName(\n"
         << "      \"" << name << "\",\n"
         << "      [&obj, &success](const auto& e){\n"
         << "        success = success && (*e >> obj." << name
         << "().emplace_back());\n"
         << "      });\n\n"
         << "    if (!success) {\n"
         << "      return false;\n"
         << "    }\n\n"
         << "    if (" << minOccurs << " > obj." << name << "().size()) {\n"
         << "      spdlog::error(\"{}: expected at least " << minOccurs
         << " elements with name '" << name <<"'\",\n"
         << "        element.location());\n"
         << "    }\n"
         << "  } // END " << name << "\n\n";
}

void generateStreamParseOptional(std::ostream &     stream,
                                 const std::string &name,
                                 const std::string &type)
// Print stream parsing code for an optional element with the specified
// 'name' and the specified 'type' to the specified 'stream'.
{

  stream << "  { // BEGIN " << name << "\n"
         << "    auto iter = kdadm::ElementUtils::getElementByTagName(\n"
         << "      \"" << name << "\",\n"
         << "      element.children().begin(),\n"
         << "      element.children().end());\n\n"
         << "    if (iter == element.children().end()) {\n"
	 << "      return true;\n"
	 << "    }\n\n"
	 << "    if (!(**iter >> obj." << name << "().emplace())) {\n"
	 << "      spdlog::error(\"{}: expected " << type <<" value\", (*iter)->location());\n"
	 << "      return false;\n"
	 << "    }\n"
	 << "  } // END " << name << "\n\n";
}

// --------------
// Struct Context
// --------------
struct Context
{
  // DATA
  std::shared_ptr<kdadm::Element> d_root;
  std::string                     d_enterpriseNs;
  std::string                     d_ns;
  std::string                     d_name;

  // ------------------------
  // Struct IncludesGenerator
  // ------------------------
  struct IncludesGenerator
  {
    // PUBLIC DATA
    std::ostream &        d_stream;
    const Context *       d_context;
    std::set<std::string> d_includes;

    // CREATORS
    IncludesGenerator(std::ostream &stream, const Context *context)
        : d_stream(stream)
        , d_context(context)
    {
      d_includes.emplace("spdlog/spdlog.h");
      d_includes.emplace("vector");
      d_includes.emplace("optional");
      d_includes.emplace("kdadm_element.h");
    }

    ~IncludesGenerator()
    {
      for (const auto& include : d_includes) {
	d_stream << "#include <" << include << ">\n";
      }
      d_stream << "\n";
    }
    
    // MANIPULATORS
    void operator()(std::shared_ptr<kdadm::Element> element)
    {
      auto cpp = cppFromInternal(element);
      if (!cpp) {
        return;
      }

      auto include = tryExtractAttribute("include", cpp);
      if (!include) {
	return;
      }

      d_includes.emplace(*include);
    }
  };

  
  // ----------------------------------
  // Struct VariableDefinitionGenerator
  // ----------------------------------
  struct VariableDefinitionGenerator
  {
    // PUBLIC DATA
    std::ostream &d_stream;
    const Context *d_context;

    // CREATORS
    VariableDefinitionGenerator(std::ostream &stream, const Context *context)
        : d_stream(stream)
        , d_context(context)
    {
      d_stream << "// DATA\n";
    }

    // MANIPULATORS
    void operator()(std::shared_ptr<kdadm::Element> element)
    {
      std::string name = extractAttribute("name", element);
      std::string type = extractAttribute("type", element);
      std::optional<std::string> value =
          tryExtractAttribute("default", element);

      size_t minOccurs = 1;
      size_t maxOccurs = 1;

      extractOccurs(&minOccurs, &maxOccurs, element);

      assert(1 == element->children().size());

      generateMemberVariableDefinition(d_stream,
                                       type,
                                       name,
                                       minOccurs,
                                       maxOccurs,
                                       element->children()[0],
                                       value);
    }
  };

  // ----------------------------------
  // Struct AccessorDefinitionGenerator
  // ----------------------------------
  struct AccessorDefinitionGenerator
  {
    // PUBLIC DATA
    std::ostream &d_stream;
    const Context *d_context;

    // CREATORS
    AccessorDefinitionGenerator(std::ostream &stream, const Context *context)
        : d_stream(stream)
        , d_context(context)
    {
      d_stream << "// ACCESSORS\n";
    }

    // MANIPULATORS
    void operator()(std::shared_ptr<kdadm::Element> element)
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

  // -------------------------------------
  // Struct ManipulatorDefinitionGenerator
  // -------------------------------------
  struct ManipulatorDefinitionGenerator
  {
    // PUBLIC DATA
    std::ostream &d_stream;
    const Context *d_context;

    // CREATORS
    ManipulatorDefinitionGenerator(std::ostream &stream, const Context *context)
        : d_stream(stream)
        , d_context(context)
    {
      d_stream << "// MANIPULATOR\n";
    }

    // MANIPULATORS
    void operator()(std::shared_ptr<kdadm::Element> element)
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

  // -----------------------------------
  // Struct StreamDefinitionGenerator
  // -----------------------------------
  struct StreamDefinitionGenerator
  {
    // PUBLIC DATA
    std::ostream &d_stream;
    const Context *d_context;

    // CREATORS
    StreamDefinitionGenerator(std::ostream &     stream,
                                 const Context *    context,
                                 const std::string &className)
        : d_stream(stream)
        , d_context(context)
    {
      d_stream << "bool operator>>(const kdadm::Element &element, "
               << className << "& obj);\n";
    }

    StreamDefinitionGenerator(const StreamDefinitionGenerator&) = delete;
    
    ~StreamDefinitionGenerator()
    {
    }
    
    // MANIPULATORS
    void operator()(std::shared_ptr<kdadm::Element> element)
    {
    }
  };

  // -----------------------------------
  // Struct StreamSpecificationGenerator
  // -----------------------------------
  struct StreamSpecificationGenerator
  {
    // PUBLIC DATA
    std::ostream &d_stream;
    const Context *d_context;

    // CREATORS
    StreamSpecificationGenerator(std::ostream &     stream,
                                 const Context *    context,
                                 const std::string &className)
        : d_stream(stream)
        , d_context(context)
    {
      d_stream << "bool operator>>(const kdadm::Element &element, "
               << className << "& obj)\n{\n";
    }

    StreamSpecificationGenerator(const StreamSpecificationGenerator&) = delete;
    
    ~StreamSpecificationGenerator()
    {
      d_stream << "  return true;\n}\n";
    }
    
    // MANIPULATORS
    void operator()(std::shared_ptr<kdadm::Element> element)
    {
      std::string name = extractAttribute("name", element);
      std::string type = extractAttribute("type", element);

      size_t minOccurs = 1;
      size_t maxOccurs = 1;

      extractOccurs(&minOccurs, &maxOccurs, element);
      
      assert(1 == element->children().size());

      if (1 == maxOccurs && 1 == minOccurs) {
	generateStreamParseManditory(d_stream, name, type);
      } else if (1 < maxOccurs) {
	generateStreamParseVector(d_stream, name, type, minOccurs);
      } else {
	generateStreamParseOptional(d_stream, name, type);
      }
    }
  };

  
  // ------------------------------
  // Struct TypeDefinitionGenerator
  // ------------------------------
  struct TypeDefinitionGenerator
  {
    // PUBLIC DATA
    std::ostream &d_stream;
    const Context *d_context;

    // CREATORS
    TypeDefinitionGenerator(std::ostream &stream, const Context *context)
        : d_stream(stream)
        , d_context(context)
    {}

    // MANIPULATORS
    void operator()(std::shared_ptr<kdadm::Element> element)
    {
      std::string name     = extractAttribute("name", element);
      auto        sequence = extractElement("xs:sequence", element);

      generateClassBanner(d_stream, name);
      d_stream << "class " << name << "\n"
               << "{\n";

      VariableDefinitionGenerator variableDefinitionGenerator(d_stream,
                                                              d_context);
      sequence->getElementsByTagName("xs:element",
                                     std::ref(variableDefinitionGenerator));

      d_stream << "public:\n"
	       << "// CREATORS\n";

      ManipulatorDefinitionGenerator manipulatorDefinitionGenerator(d_stream,
                                                                    d_context);
      sequence->getElementsByTagName("xs:element",
                                     std::ref(manipulatorDefinitionGenerator));

      AccessorDefinitionGenerator accessorDefinitionGenerator(d_stream,
                                                              d_context);
      sequence->getElementsByTagName("xs:element",
                                     std::ref(accessorDefinitionGenerator));

      d_stream << "}; // class " << name << "\n\n";

      d_stream << "// --- inline methods ---\n\n"
	       << "// " << std::string(name.size() + 6, '-') << "\n"
	       << "// Class " << name << "\n"
	       << "// " << std::string(name.size() + 6, '-') << "\n\n";

      StreamDefinitionGenerator streamDefinitionGenerator(
          d_stream, d_context, name);
      sequence->getElementsByTagName("xs:element",
                                     std::ref(streamDefinitionGenerator));
    }
  };

  // ---------------------------------
  // Struct TypeSpecificationGenerator
  // ---------------------------------
  struct TypeSpecificationGenerator
  {
    // PUBLIC DATA
    std::ostream & d_stream;
    const Context *d_context;

    // CREATORS
    TypeSpecificationGenerator(std::ostream &stream, const Context *context)
        : d_stream(stream)
        , d_context(context)
    {}

    // MANIPULATORS
    void operator()(std::shared_ptr<kdadm::Element> element)
    {
      std::string name     = extractAttribute("name", element);
      auto        sequence = extractElement("xs:sequence", element);

      StreamSpecificationGenerator streamSpecificationGenerator(
          d_stream, d_context, name);
      sequence->getElementsByTagName("xs:element",
                                     std::ref(streamSpecificationGenerator));
    }
  };

  
  void beginDocument(std::ostream &stream, const std::string &filename) const
  {
    stream << "// " << filename << std::string(80 - filename.size() - 13, ' ')
           << "-*-c++-*-\n";
  }

  void beginNamespaces(std::ostream &stream) const
  {
    stream << "namespace " << d_enterpriseNs << " {\n";
    stream << "namespace " << d_ns << " {\n\n";
  }

  void endNamespaces(std::ostream &stream) const
  {
    stream << "}; // namespace " << d_ns << "\n";
    stream << "}; // namespace " << d_enterpriseNs << "\n";
  }

  bool generateHeader() const
  {
    std::string lcNs   = d_ns;
    std::string lcName = d_name;

    std::transform(lcNs.begin(), lcNs.end(), lcNs.begin(), ::tolower);
    std::transform(lcName.begin(), lcName.end(), lcName.begin(), ::tolower);

    { // Header
      std::string   filename = lcNs + "_" + lcName + ".h";
      std::ofstream stream(filename);
      if (!stream) {
        std::cerr << "Error opening header file: '" << filename << "'.\n";
        return false;
      }

      beginDocument(stream, filename);

      {
	IncludesGenerator includesGenerator(stream, this);
	d_root->getElementsByTagName("xs:internalType", std::ref(includesGenerator));
      }
      
      beginNamespaces(stream);

      {
	TypeDefinitionGenerator typeGenerator(stream, this);
	d_root->getElementsByTagName("xs:complexType", std::ref(typeGenerator));
      }

      endNamespaces(stream);

      if (!stream) {
	return false;
      }
    }
    
    return true;
  }

  bool generateSource() const
  {
    std::string lcNs   = d_ns;
    std::string lcName = d_name;

    std::transform(lcNs.begin(), lcNs.end(), lcNs.begin(), ::tolower);
    std::transform(lcName.begin(), lcName.end(), lcName.begin(), ::tolower);

    { // Header
      std::string   filename       = lcNs + "_" + lcName + ".cpp";
      std::string   headerFilename = lcNs + "_" + lcName + ".h";

      std::ofstream stream(filename);
      if (!stream) {
        std::cerr << "Error opening source file: '" << filename << "'.\n";
        return false;
      }

      beginDocument(stream, filename);

      stream << "#include <" << headerFilename << ">\n"
             << "#include <spdlog/fmt/bundled/ostream.h>\n\n";

      beginNamespaces(stream);

      {
        TypeSpecificationGenerator typeGenerator(stream, this);
        d_root->getElementsByTagName("xs:complexType", std::ref(typeGenerator));
      }

      endNamespaces(stream);

      if (!stream) {
	return false;
      }
    }
    
    return true;
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

  Context context;
  context.d_root         = root;
  context.d_enterpriseNs = extractAttribute("enterpriseNs", root);
  context.d_ns           = extractAttribute("ns", root);
  context.d_name         = extractAttribute("name", root);

  if (!context.generateHeader()) {
    return false;
  }

  if (!context.generateSource()) {
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
