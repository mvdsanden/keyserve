// a_kstor_keystorefactory.h                                          -*-c++-*-
#ifndef INCLUDED_A_KSTOR_KEYSTOREFACTORY
#define INCLUDED_A_KSTOR_KEYSTOREFACTORY

#include <functional>
#include <memory>

namespace MvdS {

// Forward declarations
namespace ksvc {
class KeyStoreConfig;
class KeyStore;
}

namespace a_kstor {

// ======================
// Class: KeyStoreFactory
// ======================

class KeyStoreFactory
{
  // ...

  // TYPES
  typedef std::function<std::unique_ptr<ksvc::KeyStore>()> Factory;

  // DATA
  Factory d_factory;

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  KeyStoreFactory(const ksvc::KeyStoreConfig &config);
  // ...

  // MANIPULATORS
  std::unique_ptr<ksvc::KeyStore> create();

  // ACCESSORS
};

} // namespace a_kstor
} // namespace MvdS

#endif // INCLUDED_A_KSTOR_KEYSTOREFACTORY

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
