// ksvc_securitycontext.h                                             -*-c++-*-
#ifndef INCLUDED_KSVC_SECURITYCONTEXT
#define INCLUDED_KSVC_SECURITYCONTEXT

#include <functional>

namespace MvdS {
namespace ksvc {

// ======================
// Class: SecurityContext
// ======================

class SecurityContext
{
  // ...

  // TYPES

  // DATA

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  SecurityContext();
  // ...

  // MANIPULATORS

  // ACCESSORS
  virtual void validateParent(std::function<void(bool)> result,
                              std::string               parent) const = 0;
  // Validate the specified 'parent'. The specified 'result' callback is called
  // sometime in the near future with the validation result.
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_SECURITYCONTEXT

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
