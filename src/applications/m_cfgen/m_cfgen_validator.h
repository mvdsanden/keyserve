// m_cfgen_validator.h                                            -*-c++-*-
#ifndef INCLUDED_M_CFGEN_VALIDATOR
#define INCLUDED_M_CFGEN_VALIDATOR

#include <m_cfgen_commandlineargs.h>
#include <kdadm_document.h>

namespace MvdS {
namespace m_cfgen {

// ====================
// Class: Validator
// ====================

class Validator
{
  // ...

  // TYPES

  // DATA

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  Validator(const CommandlineArgs& arguments);
  // Create validator using the specified 'arguments'.

  // MANIPULATORS
  bool validate(kdadm::Document* document);
  // Validate the specified 'document'.

  // ACCESSORS
};

} // namespace m_cfgen
} // namespace MvdS

#endif // INCLUDED_M_CFGEN_VALIDATOR

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
