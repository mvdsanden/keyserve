// m_cfgen_codegeneratorfactory.cpp                                   -*-c++-*-
#include <m_cfgen_codegeneratorfactory.h>
#include <m_cfgen_cppcodegenerator.h>
#include <m_cfgen_commandlineargs.h>

#include <iostream>

namespace MvdS {
namespace m_cfgen {

// ---------------------------
// Class: CodeGeneratorFactory
// ---------------------------

// ACCESSORS
CodeGenerator *CodeGeneratorFactory::create(const CommandlineArgs& arguments) const
{
  if ("c++" == arguments.language()) {
    return new CppCodeGenerator(arguments);
  }

  std::cerr << "No code generator available for language: '" << arguments.language() << "'.\n";
  
  return nullptr;
}

} // namespace m_cfgen
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
