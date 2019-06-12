// ksvc_commandlineargs.cpp                                           -*-c++-*-
#include <ksvc_commandlineargs.h>

#include <functional>
#include <iostream>

namespace MvdS {
namespace ksvc {

namespace {

class ArgumentTable
{

  // TYPES
  struct Argument
  {
    // TYPES
    typedef std::function<size_t(CommandlineArgs *            obj,
                                 gsl::span<const char *const> arguments)>
        Parser;

    // DATA
    const std::string d_longName;
    const std::string d_shortName;
    const std::string d_description;
    Parser            d_parser;

    // CREATORS
    Argument(const std::string &longName,
             const std::string &shortName,
             const std::string &description,
             const Parser       parser)
        : d_longName(longName)
        , d_shortName(shortName)
        , d_description(description)
        , d_parser(parser)
    {}
  };

  typedef std::vector<Argument>     Arguments;
  typedef Arguments::const_iterator const_iterator;

  // DATA
  Arguments d_arguments;

  // PRIVATE ACCESSORS
  const_iterator findArgument(const std::string &name) const
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
    return 2;
  }
  
public:
  // CREATORS
  ArgumentTable()
  {
    d_arguments.emplace_back("--config", "-c", "", parseConfig);
  }

  // ACCESSORS
  size_t parseArgument(CommandlineArgs *            obj,
                       gsl::span<const char *const> arguments) const
  {
    if (arguments.empty()) {
      return 0;
    }

    const auto argIter = findArgument(arguments[0]);

    if (std::end(d_arguments) == argIter) {
      return 0;
    }

    return argIter->d_parser(obj, arguments);
  }
};

} // namespace

// ----------------------
// Class: CommandlineArgs
// ----------------------

// CREATORS
CommandlineArgs::CommandlineArgs() {}

CommandlineArgs::~CommandlineArgs() {}

// MANIPULATORS

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

// --------------------------
// Class: CommandlineArgsUtil
// --------------------------

CommandlineArgs CommandlineArgsUtil::parse(gsl::span<const char *const> args)
{
  static ArgumentTable s_table;

  typedef gsl::span<const char *const> ArgSpan;
  CommandlineArgs                      result;

  size_t index = 0;
  while (index < args.size()) {
    size_t shift = s_table.parseArgument(&result, args.subspan(index));

    if (0 == shift) {
      result.positional().emplace_back(args[index]);
      ++shift;
    }

    index += shift;
  }

  return result;
}

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
