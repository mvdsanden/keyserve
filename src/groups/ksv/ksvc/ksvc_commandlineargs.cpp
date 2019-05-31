// ksvc_commandlineargs.cpp                                           -*-c++-*-
#include <ksvc_commandlineargs.h>

namespace MvdS {
namespace ksvc {

namespace {

  struct {
    std::string d_longName;
    std::string d_shortName;
    std::string d_description;
    std::function<void(const std::string&, const std::string&)> d_cb;
  } ARGS = {};
  
} // anonymouse namespace

// ----------------------
// Class: CommandlineArgs
// ----------------------

// MANIPULATORS
void CommandlineArgs::addLong(const std::string &name,
                              const std::string &value)
{
}

void CommandlineArgs::addShort(const std::string &name,
                               const std::string &value) {}

// ACCESSORS
const CommandlineArgs::Strings &CommandlineArgs::positional() const {}

const CommandlineArgs::Strings &CommandlineArgs::configFiles() const {}

// --------------------------
// Class: CommandlineArgsUtil
// --------------------------

CommandlineArgs CommandlineArgsUtil::create(int argc, char **argv) {}

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
