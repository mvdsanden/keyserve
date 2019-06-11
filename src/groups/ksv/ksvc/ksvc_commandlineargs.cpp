// ksvc_commandlineargs.cpp                                           -*-c++-*-
#include <ksvc_commandlineargs.h>

#include <functional>
#include <iostream>

namespace MvdS {
namespace ksvc {

namespace {

  struct ArgInfo {
    // TYPES
    typedef std::function<size_t(CommandlineArgs *obj,
                              gsl::span<const char * const> arguments)>
        Parser;

    // DATA
    const std::string d_longName;
    const std::string d_shortName;
    const std::string d_description;
    Parser d_parser;
  };

  std::array<ArgInfo, 2> s_argList{
      {"--config", "-c", "",
       [](auto *obj, auto args) {
          if (2 > args.size()) {
            return 0;
          }
          obj->configFiles().emplace_back(args[1]);
          return 2;
	}}/*,
	    {"help", "h", "", [] _(obj, name, args) { return 0; }}*/};

  typedef decltype(s_argList)::const_iterator ArgIterator;
  
  ArgIterator findArgument(const std::string &name) {
    return std::find_if(
        std::begin(s_argList), std::end(s_argList), [name](const auto &arg) {
          return arg.d_shortName == name || arg.d_longName == name;
        });
  }

  size_t parseArgument(CommandlineArgs *obj,
                    gsl::span<const char *const> arguments) {    
    if (arguments.empty()) {
      return 0;
    }

    const auto argIter = findArgument(arguments[0]);

    if (std::end(s_argList) == argIter) {
      return 0;
    }

    return argIter->d_parser(obj, arguments);
  }

} // anonymouse namespace

// ----------------------
// Class: CommandlineArgs
// ----------------------

// CREATORS
CommandlineArgs::CommandlineArgs()
{
}

CommandlineArgs::~CommandlineArgs() {}

// MANIPULATORS
  
// ACCESSORS
const CommandlineArgs::Strings &CommandlineArgs::positional() const {
  return d_positional;
}

CommandlineArgs::Strings &CommandlineArgs::positional() {
  return d_positional;
}
  
const CommandlineArgs::Strings &CommandlineArgs::configFiles() const {
  return d_configFiles;
}

CommandlineArgs::Strings &CommandlineArgs::configFiles()  {
  return d_configFiles;
}
  
// --------------------------
// Class: CommandlineArgsUtil
// --------------------------

CommandlineArgs CommandlineArgsUtil::parse(gsl::span<const char * const> args)
{
  typedef gsl::span<const char *const> ArgSpan;
  CommandlineArgs result;

  size_t index = 0;
  while (index < args.size()) {
    size_t shift = parseArgument(&result, args.subspan(index));

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
