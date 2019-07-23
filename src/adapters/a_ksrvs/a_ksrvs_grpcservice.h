// a_ksrvs_grpcservice.h                                              -*-c++-*-
#ifndef INCLUDED_A_KSRVS_GRPCSERVICE
#define INCLUDED_A_KSRVS_GRPCSERVICE

#include <ksvc_service.h>

namespace MvdS {

// Forward declarations.
namespace ksvc {
class SecurityManager;
class Configuration;
class ServiceConfig;
}

namespace a_ksrvs {

// ==================
// Class: GrpcService
// ==================

class GrpcService : public ksvc::Service
{
  // ...

  // TYPES

  // DATA
  ksvc::SecurityManager *d_securityManager;

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  GrpcService(ksvc::SecurityManager *    securityManager,
              const ksvc::ServiceConfig &config);
  // Create gRPC service using the specified 'securityManager' and the specified
  // 'config'.

  ~GrpcService();

  // MANIPULATORS
  void start() override;
  // Start asynchornous service.

  void stop() override;
  // Stop asynchronous service.

  // ACCESSORS
};

} // namespace a_ksrvs
} // namespace MvdS

#endif // INCLUDED_A_KSRVS_GRPCSERVICE

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
