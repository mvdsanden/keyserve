// a_kscrypt_cryptofactory.cpp                                        -*-c++-*-
#include <a_kscrypt_cryptofactory.h>
#include <a_kscrypt_dummycrypto.h>

#include <ksvc_configuration.h>

namespace MvdS {
namespace a_kscrypt {

// --------------------
// Class: CryptoFactory
// --------------------

// CREATORS
CryptoFactory::CryptoFactory(const ksvc::CryptoConfig &config)
{

  if ("dummy" == config.backend()) {
    d_factory = [config]() { return std::make_unique<DummyCrypto>(config); };
  }
  
}

// MANIPULATORS
std::unique_ptr<ksvc::Crypto> CryptoFactory::create()
{
  if (!d_factory) {
    return nullptr;
  }

  return std::move(d_factory());
}

// MANIPULATORS

// ACCESSORS

} // namespace a_kscrypt
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
