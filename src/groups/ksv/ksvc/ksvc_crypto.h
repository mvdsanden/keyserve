// ksvc_crypto.h                                                      -*-c++-*-
#ifndef INCLUDED_KSVC_CRYPTO
#define INCLUDED_KSVC_CRYPTO

#include <ksvc_resultfunction.h>

#include <memory>

namespace MvdS {
namespace ksvc {

// Forward declaration
class CryptoKeyVersion;
class CryptoKeyVersionTemplate;
  
// =============
// Class: Crypto
// =============

class Crypto
{
  // ...

  // TYPES

  // DATA

  // PRIVATE MANIPULATORS

public:
  // CREATORS

  // MANIPULATORS
  virtual void
  createCryptoKey(ResultFunction<std::shared_ptr<CryptoKeyVersion>> result,
                  CryptoKeyVersionTemplate versionTemplate) = 0;
  // Create new crypto key version using the specified 'versionTemplate'.

  // ACCESSORS
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_CRYPTO

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
