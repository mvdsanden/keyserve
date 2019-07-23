// a_ksrvs_servicefactory.h                                           -*-c++-*-
#ifndef INCLUDED_A_KSRVS_SERVICEFACTORY
#define INCLUDED_A_KSRVS_SERVICEFACTORY

#include <vector>
#include <memory>

namespace MvdS {

// Forward declarations.
namespace ksvc {
class SecurityManager;
class Configuration;
class Service;
}
  
namespace a_ksrvs {
  
// =====================
// Class: ServiceFactory
// =====================

class ServiceFactory
{
  // Provides a factory for services.

  // TYPES

  // DATA
  ksvc::SecurityManager *    d_securityManager;
  const ksvc::Configuration &d_config;

  // PRIVATE MANIPULATORS

public:
  // PUBLIC TYPES
  typedef std::vector<std::unique_ptr<ksvc::Service>> Services;
  
  // CREATORS
  ServiceFactory(ksvc::SecurityManager *    securityManager,
                 const ksvc::Configuration &config);
  // Create service factor using the specified 'securityManager' and the
  // specified 'config'.

  // MANIPULATORS
  Services createConfigured();
  // Create all configured service. Return the vector of services.

  // ACCESSORS
};

} // namespace a_ksrvs
} // namespace MvdS

#endif // INCLUDED_A_KSRVS_SERVICEFACTORY

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
