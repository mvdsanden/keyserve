// ksvc_commandlineargs.h                                             -*-c++-*-
#ifndef INCLUDED_KSVC_COMMANDLINEARGS
#define INCLUDED_KSVC_COMMANDLINEARGS

#include <string>
#include <vector>
#include <memory>

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
  void addLong(const std::string& name, const std::string& value);
  // Add a long argument, that starts with two dashes ("--").

  void addShort(const std::string& name, const std::string& value);
  // Add a short argument, that starts with one dash ("-").
  
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
