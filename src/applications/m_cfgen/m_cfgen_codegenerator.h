// m_cfgen_codegenerator.h                                            -*-c++-*-
#ifndef INCLUDED_M_CFGEN_CODEGENERATOR
#define INCLUDED_M_CFGEN_CODEGENERATOR

#include <iosfwd>

namespace MvdS {
  
namespace kdadm { class Document; } // forward declaration
  
namespace m_cfgen {

// ====================
// Class: CodeGenerator
// ====================

class CodeGenerator
{
  // ...
public:
  // MANIPULATORS
  virtual bool generate(const kdadm::Document &document) = 0;
  // Generate code for the specified 'document'. Return 'true' on success.
};

} // namespace m_cfgen
} // namespace MvdS

#endif // INCLUDED_M_CFGEN_CODEGENERATOR

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
