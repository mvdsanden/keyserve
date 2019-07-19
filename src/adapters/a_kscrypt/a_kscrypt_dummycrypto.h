// a_kscrypt_dummycrypto.h                                            -*-c++-*-
#ifndef INCLUDED_A_KSCRYPT_DUMMYCRYPTO
#define INCLUDED_A_KSCRYPT_DUMMYCRYPTO

#include <ksvc_crypto.h>

namespace MvdS {

// Forward declarations
namespace ksvc {
class CryptoConfig;
class CryptoKeyVersion;
class CryptoKeyVersionTemplate;
}; // namespace ksvc

namespace a_kscrypt {

// ==================
// Class: DummyCrypto
// ==================

  class DummyCrypto : public ksvc::Crypto
{
  // ...

  // TYPES

  // DATA

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  DummyCrypto(const ksvc::CryptoConfig& config);
  // ...

  // MANIPULATORS
  void createCryptoKey(
      ksvc::ResultFunction<std::shared_ptr<ksvc::CryptoKeyVersion>> result,
      const ksvc::CryptoKeyVersionTemplate &versionTemplate) override;
  // Create new crypto key version using the specified 'versionTemplate'.

  // ACCESSORS
};

} // namespace a_kscrypt
} // namespace MvdS

#endif // INCLUDED_A_KSCRYPT_DUMMYCRYPTO

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
