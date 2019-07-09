// ksvc_configurationutil.h                                           -*-c++-*-
#ifndef INCLUDED_KSVC_CONFIGURATIONUTIL
#define INCLUDED_KSVC_CONFIGURATIONUTIL

namespace MvdS {
namespace ksvc {

// Forward declaration
class Configuration;
class CommandlineArgs;

// ========================
// Class: ConfigurationUtil
// ========================

class ConfigurationUtil
{
  // ...

  // TYPES

  // DATA

  // PRIVATE MANIPULATORS

public:
  // CLASS METHODS
  static bool readConfiguration(Configuration *config, const CommandlineArgs& args);
  // Determine config source from the specified 'args' and read it into the
  // specified 'config'. Return 'true' on success.

  // CREATORS

  // MANIPULATORS

  // ACCESSORS
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_CONFIGURATIONUTIL

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
