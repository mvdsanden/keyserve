// m_cfgen_codegenerator.h                                            -*-c++-*-
#ifndef INCLUDED_M_CFGEN_CODEGENERATOR
#define INCLUDED_M_CFGEN_CODEGENERATOR

#include <m_cfgen_commandlineargs.h>
#include <kdadm_document.h>

namespace MvdS {
namespace m_cfgen {

// ====================
// Class: CodeGenerator
// ====================

class CodeGenerator
{
  // ...

  // TYPES

  // DATA

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  CodeGenerator(const CommandlineArgs& arguments);
  // Create code generator using the specified 'arguments'.

  // MANIPULATORS
  bool generate(std::ostream& stream, const kdadm::Document& document);
  // Generate the code to the specified 'stream' using the specified 'document'
  // as source.

  // ACCESSORS
};

} // namespace m_cfgen
} // namespace MvdS

#endif // INCLUDED_M_CFGEN_CODEGENERATOR

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
