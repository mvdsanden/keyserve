// m_cfgen_commandlineargs.h                                             -*-c++-*-
#ifndef INCLUDED_M_CFGEN_COMMANDLINEARGS
#define INCLUDED_M_CFGEN_COMMANDLINEARGS

#include <memory>
#include <string>
#include <vector>

#include <gsl/span>

namespace MvdS {
namespace m_cfgen {

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
  Strings     d_positional;
  std::string d_input;
  std::string d_outputPath;
  std::string d_language = "c++";
  bool        d_printUsage = false;

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  CommandlineArgs();

  virtual ~CommandlineArgs();

  // MANIPULATORS
  Strings &positional();
  // Return positional arguments.

  std::string &input();
  // Return input filename.

  std::string &outputPath();
  // Return output path.

  std::string &language();
  // Return output language.
  
  void printUsage(bool on);
  // Set print usage flag to the specified 'on'.
  
  // ACCESSORS
  const Strings &positional() const;
  // Return positional arguments.

  const std::string &input() const;
  // Return input filename.

  const std::string &outputPath() const;
  // Return output path.

  const std::string &language() const;
  // Return output language.
  
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

} // namespace m_cfgen
} // namespace MvdS

#endif // INCLUDED_M_CFGEN_COMMANDLINEARGS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
