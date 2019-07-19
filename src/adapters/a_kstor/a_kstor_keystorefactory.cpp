// a_kstor_keystorefactory.cpp                                        -*-c++-*-
#include <a_kstor_keystorefactory.h>
#include <a_kstor_memorykeystore.h>

#include <ksvc_configuration.h>

namespace MvdS {
namespace a_kstor {

// ----------------------
// Class: KeyStoreFactory
// ----------------------

// CREATORS
KeyStoreFactory::KeyStoreFactory(const ksvc::KeyStoreConfig &config)
{

  if ("memory" == config.backend()) {
    d_factory = [config]() { return std::make_unique<MemoryKeyStore>(config); };
  }
  
}

// MANIPULATORS
std::unique_ptr<ksvc::KeyStore> KeyStoreFactory::create()
{
  if (!d_factory) {
    return nullptr;
  }

  return d_factory();
}

// ACCESSORS

} // namespace a_kstor
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
