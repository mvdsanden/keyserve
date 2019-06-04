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
    typedef std::function<void(CommandlineArgs::Data *data,
                               const std::string &name,
                               const std::string &value)>
        Setter;

    // DATA
    const std::string d_longName;
    const std::string d_shortName;
    const std::string d_description;
    Setter d_setter;
  };

#define _(x, y, z) (CommandlineArgs::Data *x, const std::string &y, const std::string &z)
  
  std::array<ArgInfo, 1> s_argList{{"config", "c", "", [] _(data, name, value) {
                                      data->d_configFiles.emplace_back(value);
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
bool CommandlineArgs::parseLong(const std::string &name,
                                const std::string &value) {
  const auto argIter = findArgLong(name);

  if (std::end(s_argList) == argIter) {
    return false;
  }

  argIter->d_setter(d_data.get(), name, value);
  return true;
}

bool CommandlineArgs::parseShort(const std::string &name,
                                 const std::string &value) {
  const auto argIter = findArgShort(name);

  if (std::end(s_argList) == argIter) {
    return false;
  }

  argIter->d_setter(d_data.get(), name, value);
  return true;
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

CommandlineArgs CommandlineArgsUtil::create(int argc, char **argv) {}

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
