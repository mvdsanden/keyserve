// ksvc_commandlineargs.h                                             -*-c++-*-
#ifndef INCLUDED_KSVC_COMMANDLINEARGS
#define INCLUDED_KSVC_COMMANDLINEARGS

#include <memory>
#include <string>
#include <vector>

#include <gsl/span>

namespace MvdS {
namespace ksvc {

// ======================
// Class: CommandlineArgs
// ======================

class CommandlineArgs
{
  // Provides a container for commandline arguments.

public:
  // PUBLIC TYPES
  typedef std::vector<std::string> Strings;
  struct Data;

private:
  // DATA  
  Strings d_positional;
  Strings d_configFiles;
  bool    d_printUsage;

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  CommandlineArgs();

  virtual ~CommandlineArgs();

  // MANIPULATORS
  Strings &positional();
  // Return positional arguments.

  Strings &configFiles();
  // Return all specified configuration files.

  void printUsage(bool on);
  // Set print usage flag to the specified 'on'.
  
  // ACCESSORS
  const Strings &positional() const;
  // Return positional arguments.

  const Strings &configFiles() const;
  // Return all specified configuration files.

  bool printUsage() const;
  // Return 'true' if the print usage flag is set.
};

// ==========================
// Class: CommandlineArgsUtil
// ==========================

class CommandlineArgsUtil
{
public:
  static void parse(CommandlineArgs *result, gsl::span<const char *const> arguments);
  // Parse the specified 'argc' arguments from the specified 'argv' and store
  // into the specified 'result'.

  static void printUsage(std::ostream *stream, gsl::span<const char *const> arguments);
  // Print usage to the specified 'stream' using the specified 'arguments' to
  // extract the name of the application.
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_COMMANDLINEARGS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
