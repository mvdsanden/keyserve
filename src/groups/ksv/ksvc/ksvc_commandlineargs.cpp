// ksvc_commandlineargs.cpp                                           -*-c++-*-
#include <ksvc_commandlineargs.h>

#include <functional>

namespace MvdS {
namespace ksvc {

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

  std::array<ArgInfo, 2> s_argList{
      {"config", "c", "",
       [] _(obj, name, args) {
         if (args.empty()) {
           return -1;
         }
         obj->configFiles().emplace_back(args[0]);
         return 1;
	}}/*,
	    {"help", "h", "", [] _(obj, name, args) { return 0; }}*/};

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
  //  ArgSpan args(const_cast<const char **>(argv), argc);

  for (size_t i = 0; i < args.size(); ++i) {

    const char *name = args[i];

    if ('-' == name[0]) {

      if ('-' == name[1]) {

    	if (parseLong(&result, name + 2, args.subspan(i+1))) {
	  continue;
    	}
	
      } else {

    	if (parseShort(&result, name + 1, args.subspan(i+1))) {
	  continue;
    	}
	
      }

    }

    result.positional().emplace_back(name);
  }

}

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
