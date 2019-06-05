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
  std::unique_ptr<Data> d_data;
  
  // PRIVATE MANIPULATORS

public:
  // CREATORS
  CommandlineArgs();

  virtual ~CommandlineArgs();
  
  // MANIPULATORS
  int parseLong(const std::string &name, gsl::span<const char * const> arguments);
  // Parse a long argument with the specified 'name' and the specified
  // 'argc' count arguments in the specified 'argv'. Return '-1' on failure
  // and the number of parsed arguments otherwise.

  int parseShort(const std::string &name, gsl::span<const char * const> arguments);
  // Parse a long argument with the specified 'name' and the specified
  // 'argc' count arguments in the specified 'argv'. Return '-1' on failure
  // and the number of parsed arguments otherwise.


  void appendPositional(const std::string& value);
  // Append the specified 'value' to the positional arguments list.
  
  // ACCESSORS
  const Strings& positional() const;
  // Return positional arguments.

  const Strings& configFiles() const;
  // Return all specified configuration files.
};

// ==========================
// Class: CommandlineArgsUtil
// ==========================

class CommandlineArgsUtil {
public:
  static CommandlineArgs create(int argc, char **argv);
  // Parse the specified 'argc' arguments from the specified 'argv'.
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_COMMANDLINEARGS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
