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
    typedef std::function<int(CommandlineArgs *obj,
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
  (CommandlineArgs * x, const std::string &y, gsl::span<const char * const> z)->int

  std::array<ArgInfo, 1> s_argList{{"config", "c", "", [] _(obj, name, args) {
                                      if (args.empty()) {
                                        return -1;
                                      }
                                      obj->appendConfigFile(args[0]);
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

  int parseLong(CommandlineArgs *obj, const std::string &name,
                gsl::span<const char *const> arguments) {
    const auto argIter = findArgLong(name);

    if (std::end(s_argList) == argIter) {
      return -1;
    }

    return argIter->d_parser(obj, name, arguments);
  }

  int parseShort(CommandlineArgs *obj, const std::string &name,
                 gsl::span<const char *const> arguments) {
    const auto argIter = findArgShort(name);

    if (std::end(s_argList) == argIter) {
      return -1;
    }

    return argIter->d_parser(obj, name, arguments);
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
void CommandlineArgs::appendPositional(const std::string &value)
{
  d_data->d_positional.emplace_back(value);
}

void CommandlineArgs::appendConfigFile(const std::string& filename)
{
  d_data->d_configFiles.emplace_back(filename);
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

CommandlineArgs CommandlineArgsUtil::parse(int argc, char **argv)
{
  typedef gsl::span<const char *const> ArgSpan;
  CommandlineArgs result;
  ArgSpan args(const_cast<const char **>(argv), argc);

  for (size_t i = 0; i < argc; ++i) {

    const char *name = args[i];

    if ('-' == name[0]) {

      if ('-' == name[1]) {

    	if (parseLong(&result, name, args.subspan(i+1))) {
	  continue;
    	}
	
      } else {

    	if (parseShort(&result, name, args.subspan(i+1))) {
	  continue;
    	}
	
      }

    }

    result.appendPositional(name);
  }

}

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
