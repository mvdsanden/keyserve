// ksvc_service.h                                                     -*-c++-*-
#ifndef INCLUDED_KSVC_SERVICE
#define INCLUDED_KSVC_SERVICE

namespace MvdS {
namespace ksvc {

// ==============
// Class: Service
// ==============

class Service
{
  // ...

  // TYPES

  // DATA

  // PRIVATE MANIPULATORS

public:
  // CREATORS

  // MANIPULATORS
  virtual void start() = 0;
  // Start asynchornous service.

  virtual void stop() = 0;
  // Stop asynchronous service.

  // ACCESSORS
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_SERVICE

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
