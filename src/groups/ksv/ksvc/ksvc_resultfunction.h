// ksvc_resultfunction.h                                              -*-c++-*-
#ifndef INCLUDED_KSVC_RESULTFUNCTION
#define INCLUDED_KSVC_RESULTFUNCTION

#include <functional>

namespace MvdS {
namespace ksvc {

// ===================
// Struct ResultStatus
// ===================

struct ResultStatus
{
  // TYPES
  enum Type
  {

    e_success,
    e_notFound,
    e_timedOut,
    e_waiting,
    e_exists,
    e_denied
  };

  // DATA
  Type d_value;

  // CREATORS
  ResultStatus(Type value)
      : d_value(value)
  {}

  // ACCESSORS
       operator Type() const { return d_value; }
  bool isSuccess() const { return e_success == d_value; }
};

// =====================
// Class: ResultFunction
// =====================
template <class T>
using ResultFunction = std::function<void(const ResultStatus &, T)>;

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_RESULTFUNCTION

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
