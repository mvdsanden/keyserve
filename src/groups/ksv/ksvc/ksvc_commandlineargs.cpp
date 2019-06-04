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
  
  struct {
    // DATA
    const std::string d_longName;
    const std::string d_shortName;
    const std::string d_description;
    std::function<void(CommandlineArgs::Data *data, const std::string &name,
                       const std::string &value)>
        d_cb;
  } ARGS[] = {{"config", "c", "", [] _(data, name, value) {
                 data->d_configFiles.emplace_back(value);
               }}};

#undef _
  
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
  const auto end = ARGS + sizeof(ARGS) / sizeof(ARGS[0]);
  auto argIter = std::find_if(ARGS, end, [name](const auto &arg) {
    return name == arg.d_longName;
  });

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
