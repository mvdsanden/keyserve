// m_cfgen_cppcodegenerator.h                                         -*-c++-*-
#ifndef INCLUDED_M_CFGEN_CPPCODEGENERATOR
#define INCLUDED_M_CFGEN_CPPCODEGENERATOR

#include <m_cfgen_codegenerator.h>

namespace MvdS {
namespace m_cfgen {

// Forward declaration
class CommandlineArgs;
  
// =======================
// Class: CppCodeGenerator
// =======================

class CppCodeGenerator : public CodeGenerator
{
  // ...

  // TYPES

  // DATA

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  CppCodeGenerator(const CommandlineArgs& arguments);
  // ...

  // MANIPULATORS
  bool generate(const kdadm::Document &document) override;
  // Generate code for the specified 'document'. Return 'true' on success.

  // ACCESSORS
};

} // namespace m_cfgen
} // namespace MvdS

#endif // INCLUDED_M_CFGEN_CPPCODEGENERATOR

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
