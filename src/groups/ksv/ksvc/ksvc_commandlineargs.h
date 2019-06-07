// ksvc_commandlineargs.h                                             -*-c++-*-
#ifndef INCLUDED_KSVC_COMMANDLINEARGS
#define INCLUDED_KSVC_COMMANDLINEARGS

#include <string>
#include <vector>
#include <memory>

#include <gsl/span>

namespace MvdS {
namespace ksvc {

// ======================
// Class: CommandlineArgs
// ======================

class CommandlineArgs {
  // ...

public:

  // PUBLIC TYPES
  typedef std::vector<std::string> Strings; 
  struct Data;
 
private:  

  // DATA
  Strings d_positional;
  Strings d_configFiles;
  
  // PRIVATE MANIPULATORS

public:
  // CREATORS
  CommandlineArgs();

  virtual ~CommandlineArgs();
  
  // MANIPULATORS

  // ACCESSORS
  const Strings& positional() const;
  // Return positional arguments.

  Strings& positional();
  // Return positional arguments.
  
  const Strings& configFiles() const;
  // Return all specified configuration files.

  Strings& configFiles();
  // Return all specified configuration files.
};

// ==========================
// Class: CommandlineArgsUtil
// ==========================

class CommandlineArgsUtil {
public:
  static CommandlineArgs parse(gsl::span<const char * const> arguments);
  // Parse the specified 'argc' arguments from the specified 'argv'.
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_COMMANDLINEARGS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
