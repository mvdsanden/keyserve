// a_kscrypt_cryptofactory.h                                          -*-c++-*-
#ifndef INCLUDED_A_KSCRYPT_CRYPTOFACTORY
#define INCLUDED_A_KSCRYPT_CRYPTOFACTORY

#include <functional>
#include <memory>

namespace MvdS {

// Forward declarations
namespace ksvc {
class CryptoConfig;
class Crypto;
} // namespace ksvc

namespace a_kscrypt {

// ====================
// Class: CryptoFactory
// ====================

class CryptoFactory
{
  // ...

  // TYPES
  typedef std::function<std::unique_ptr<ksvc::Crypto>()> Factory;

  // DATA
  Factory d_factory;

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  CryptoFactory(const ksvc::CryptoConfig &config);
  // ...

  // MANIPULATORS
  std::unique_ptr<ksvc::Crypto> create();
  // Create new crypto. Return the crypto or nullptr if the configured
  // type was unknown.

  // ACCESSORS
};

} // namespace a_kscrypt
} // namespace MvdS

#endif // INCLUDED_A_KSCRYPT_CRYPTOFACTORY

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
