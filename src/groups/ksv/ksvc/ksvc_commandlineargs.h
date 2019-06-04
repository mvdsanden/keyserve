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
  bool parseLong(const std::string& name, const std::string& value);
  // Parse a long argument with the specified 'name' and the specified 'value'.
  // Return 'true' on success, false otherwise.

  bool parseShort(const std::string& name, const std::string& value);
  // Parse a short argument with the specified 'name' and the specified 'value'.
  // Return 'true' on success, false otherwise.
  
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
