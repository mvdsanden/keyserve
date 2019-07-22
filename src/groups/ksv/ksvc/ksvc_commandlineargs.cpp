// ksvc_commandlineargs.cpp                                           -*-c++-*-
#include <ksvc_commandlineargs.h>

#include <functional>
#include <iostream>

namespace MvdS {
namespace ksvc {

namespace {

typedef std::function<size_t(CommandlineArgs *            obj,
                             gsl::span<const char *const> arguments)>
    ArgumentParser;

// ---------------
// Struct Argument
// ---------------
  
struct Argument
{
  // TYPES

  // DATA
  const std::string d_longName;
  const std::string d_shortName;
  ArgumentParser    d_parser;
  const std::string d_description;
};

// -------------------
// Class ArgumentTable
// -------------------

class ArgumentTable
{

  // TYPES
  typedef std::vector<Argument>     Arguments;
  typedef Arguments::const_iterator const_iterator;

  // DATA
  Arguments d_arguments;

  // PRIVATE ACCESSORS
  const_iterator findArgument(const std::string &name) const
  // Find the argument with the specified 'name' in 'd_arguments'. Return an
  // iterator to it or the end of iterator if not found.
  {
    return std::find_if(std::begin(d_arguments),
                        std::end(d_arguments),
                        [name](const auto &arg) {
                          return arg.d_shortName == name ||
                                 arg.d_longName == name;
                        });
  }

  // PRIVATE CLASS METHODS
  static size_t parseConfig(CommandlineArgs *            obj,
                            gsl::span<const char *const> args)
  {
    if (2 > args.size()) {
      return 0;
    }
    obj->configFiles().emplace_back(args[1]);
    return 2; // parsed two elements from 'args'.
  }

  static size_t parseHelp(CommandlineArgs *            obj,
                          gsl::span<const char *const> args)
  {
    if (1 > args.size()) {
      return 0;
    }
    obj->printUsage(true);
    return 1; // parsed one element from 'args'.
  }

  
public:
  // CREATORS
  ArgumentTable()
  {
    append("--config", "-c", parseConfig, "Configuration file to use.");
    append("--help", "-h", parseHelp, "Print usage information");
  }

  // CLASS METHODS
  static ArgumentTable *singleton()
  // Return singleton object.
  {
    static ArgumentTable s_instance;
    return &s_instance;
  }
  
  // MANIPULATORS
  bool append(const std::string &shortName,
              const std::string &longName,
              ArgumentParser     parser,
              const std::string &description)
  // Append an argument parser for the specified 'longName' and the specified
  // 'shortName'. Uses the specified 'parser' to process the commandline
  // argument and uses the specified 'description' to generate usage
  // information.
  {
    d_arguments.emplace_back(
        (Argument){shortName, longName, parser, description});
    return true;
  }
  
  // ACCESSORS
  size_t parseArgument(CommandlineArgs *            obj,
                       gsl::span<const char *const> arguments) const
  // Parse the specified 'arguments'. If a matching argument parser is found it
  // is called with the specified 'obj'. Return the number of 'arguments'
  // parsed.
  {
    if (arguments.empty()) {
      return 0;
    }

    const auto i = findArgument(arguments[0]);
    if (std::end(d_arguments) == i) {
      return 0;
    }

    return i->d_parser(obj, arguments);
  }

  void printUsage(std::ostream *stream, gsl::span<const char *const> arguments)
  {
    if (!arguments.empty()) {
      *stream << arguments[0];
    }

    for (const Argument& arg : d_arguments) {
      *stream << " [" << arg.d_shortName << "|" << arg.d_longName << "]";
    }

    *stream << "\n";
  }
};

} // namespace

// ----------------------
// Class: CommandlineArgs
// ----------------------

// CREATORS
CommandlineArgs::CommandlineArgs()
  : d_printUsage(false)
{}

CommandlineArgs::~CommandlineArgs() {}

// MANIPULATORS
void CommandlineArgs::printUsage(bool on)
{
  d_printUsage = on;
}

// ACCESSORS
const CommandlineArgs::Strings &CommandlineArgs::positional() const
{
  return d_positional;
}

CommandlineArgs::Strings &CommandlineArgs::positional() { return d_positional; }

const CommandlineArgs::Strings &CommandlineArgs::configFiles() const
{
  return d_configFiles;
}

CommandlineArgs::Strings &CommandlineArgs::configFiles()
{
  return d_configFiles;
}

bool CommandlineArgs::printUsage() const
{
  return d_printUsage;
}
  
// --------------------------
// Class: CommandlineArgsUtil
// --------------------------

void CommandlineArgsUtil::parse(CommandlineArgs *            result,
                                gsl::span<const char *const> args)
{
  typedef gsl::span<const char *const> ArgSpan;

  ArgumentTable *table = ArgumentTable::singleton();
  
  size_t index = 0;
  while (index < args.size()) {
    size_t shift = table->parseArgument(result, args.subspan(index));

    if (0 == shift) {
      result->positional().emplace_back(args[index]);
      ++shift;
    }

    index += shift;
  }
}

void CommandlineArgsUtil::printUsage(std::ostream *               stream,
                                     gsl::span<const char *const> arguments)
{
  ArgumentTable::singleton()->printUsage(stream, arguments);
}
  
} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
