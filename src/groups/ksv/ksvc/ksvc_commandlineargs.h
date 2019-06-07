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
  void appendPositional(const std::string& value);
  // Append the specified 'value' to the positional arguments list.

  void appendConfigFile(const std::string& filename);
  // Append the specified 'filename' to the list of configuration files.
  
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
  static CommandlineArgs parse(int argc, char **argv);
  // Parse the specified 'argc' arguments from the specified 'argv'.
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_COMMANDLINEARGS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
