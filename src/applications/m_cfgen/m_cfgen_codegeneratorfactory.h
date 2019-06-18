// m_cfgen_codegeneratorfactory.h                                     -*-c++-*-
#ifndef INCLUDED_M_CFGEN_CODEGENERATORFACTORY
#define INCLUDED_M_CFGEN_CODEGENERATORFACTORY

#include <string>

namespace MvdS {
namespace m_cfgen {

// forward declarations
class CodeGenerator;
class CommandlineArgs;

// ===========================
// Class: CodeGeneratorFactory
// ===========================

class CodeGeneratorFactory
{
  // ...

public:
  // CREATORS

  // ACCESSORS
  CodeGenerator *create(const CommandlineArgs& arguments) const;
};

} // namespace m_cfgen
} // namespace MvdS

#endif // INCLUDED_M_CFGEN_CODEGENERATORFACTORY

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
