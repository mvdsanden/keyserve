// ksvc_requesthandler.h                                              -*-c++-*-
#ifndef INCLUDED_KSVC_REQUESTHANDLER
#define INCLUDED_KSVC_REQUESTHANDLER

#include <ksvc_resultfunction.h>

#include <memory>

namespace MvdS {
namespace ksvc {

// Forward declaration.
class SecurityManager;
class CreateKeyRingRequest;
class CreateCryptoKeyRequest;
class KeyRing;
class CryptoKey;

// =====================
// Class: RequestHandler
// =====================

class RequestHandler
{
  // ...

  // TYPES

  // DATA
  SecurityManager *d_securityManager;

  // PRIVATE MANIPULATORS
public:
  // CREATORS
  RequestHandler(SecurityManager *securityManager);
  // Create request handler that uses the specified 'securityManager'.

  // MANIPULATORS
  void operator()(ResultFunction<std::shared_ptr<KeyRing>> result,
                  const CreateKeyRingRequest &             request);
  // Handle CreateKeyRing requests.

  void operator()(ResultFunction<std::shared_ptr<CryptoKey>> result,
                  const CreateCryptoKeyRequest &             request);
  // Handle CreateCryptoKey requests.

  // ACCESSORS
};

} // namespace ksvc
} // namespace MvdS

#endif // INCLUDED_KSVC_REQUESTHANDLER

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
