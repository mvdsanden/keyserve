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

#define _(x, y, z) (CommandlineArgs::Data *x, const std::string &y, const std::string &z)
  
  struct ArgInfo {
    // DATA
    const std::string d_longName;
    const std::string d_shortName;
    const std::string d_description;
    std::function<void(CommandlineArgs::Data *data, const std::string &name,
                       const std::string &value)>
        d_cb;
  };

  ArgInfo s_argList[] = {{"config", "c", "", [] _(data, name, value) {
                       data->d_configFiles.emplace_back(value);
                     }}};

  auto s_argList[] = std::make_{{"config", "c", "", [] _(data, name, value) {
                       data->d_configFiles.emplace_back(value);
                     }}};

  
#undef _

  const ArgInfo *findArg(const std::string &name,
                         const std::function < bool(const std::string &name,
                                                    const ArgInfo &arg) &
                             cmp) {
    const auto end = s_argList + sizeof(s_argList) / sizeof(s_argList[0]);
    auto argIter = std::find_if(s_argList, end, cmp);

    if (end == argIter) {
      return;
    }
  }

  const ArgInfo *findArgLong(const std::string& name)
  {
    return findArg(name,
                   [name](const auto &arg) { return name == arg.d_longName; });
  }

  const ArgInfo *findArgShort(const std::string& name)
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
void CommandlineArgs::addLong(const std::string &name,
                              const std::string &value)
{
  ArgInfo *arg = findArgLong(name);

  if (end == argIter) {
    return;
  }

  argIter->d_cb(d_data.get(), name, value);
}

void CommandlineArgs::addShort(const std::string &name,
                               const std::string &value) {}

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
