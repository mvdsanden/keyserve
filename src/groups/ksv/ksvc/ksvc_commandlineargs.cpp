// ksvc_commandlineargs.cpp                                           -*-c++-*-
#include <ksvc_commandlineargs.h>

#include <functional>

namespace MvdS {
namespace ksvc {

struct CommandlineArgs::Data
{
  // DATA
  Strings d_positional;
  Strings d_configFiles;
};

namespace {

 
  struct ArgInfo {
    // TYPES
    typedef std::function<int(CommandlineArgs::Data *data,
                              const std::string &name,
                              gsl::span<const char * const> arguments)>
        Parser;

    // DATA
    const std::string d_longName;
    const std::string d_shortName;
    const std::string d_description;
    Parser d_parser;
  };

#define _(x, y, z)                                                             \
  (CommandlineArgs::Data * x, const std::string &y, gsl::span<const char * const> z)->int

  std::array<ArgInfo, 1> s_argList{{"config", "c", "", [] _(data, name, args) {
                                      if (args.empty()) {
                                        return -1;
                                      }
                                      data->d_configFiles.emplace_back(args[0]);
                                      return 1;
                                    }}};

#undef _

  typedef decltype(s_argList)::const_iterator ArgIterator;
  
  ArgIterator findArg(const std::string &name,
                         std::function<bool(const ArgInfo &arg)> cmp) {
    return std::find_if(std::begin(s_argList), std::end(s_argList), cmp);
  }

  ArgIterator findArgLong(const std::string& name)
  {
    return findArg(name,
                   [name](const auto &arg) { return name == arg.d_longName; });
  }

  ArgIterator findArgShort(const std::string& name)
  {
    return findArg(name,
                   [name](const auto &arg) { return name == arg.d_shortName; });
  }

  
} // anonymouse namespace

// ----------------------
// Class: CommandlineArgs
// ----------------------

// CREATORS
CommandlineArgs::CommandlineArgs()
  : d_data(new Data)
{
}

CommandlineArgs::~CommandlineArgs() {}

// MANIPULATORS
int CommandlineArgs::parseLong(const std::string &name, gsl::span<const char * const> arguments) {
  const auto argIter = findArgLong(name);

  if (std::end(s_argList) == argIter) {
    return -1;
  }

  return argIter->d_parser(d_data.get(), name, arguments);
}

int CommandlineArgs::parseShort(const std::string &name, gsl::span<const char * const> arguments) {
  const auto argIter = findArgShort(name);

  if (std::end(s_argList) == argIter) {
    return -1;
  }

  return argIter->d_parser(d_data.get(), name, arguments);
}

void CommandlineArgs::appendPositional(const std::string &value)
{
  d_data->d_positional.emplace_back(value);
}

// ACCESSORS
const CommandlineArgs::Strings &CommandlineArgs::positional() const {
  return d_data->d_positional;
}

const CommandlineArgs::Strings &CommandlineArgs::configFiles() const {
  return d_data->d_configFiles;
}

// --------------------------
// Class: CommandlineArgsUtil
// --------------------------

CommandlineArgs CommandlineArgsUtil::create(int argc, char **argv)
{
  CommandlineArgs result;

  for (char **arg = argv; nullptr != *argv; ++arg) {

    // char *argName = arg[0];
    // char *argValue = arg[1];

    // if ('-' == argName[0]) {

    //   if ('-' == argName[1]) {

    // 	if (!result.parseLong(arg + 2)) {
    // 	  result.appendPositional(*arg);
    // 	}
	
    //   }

    // }

  }

}

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
