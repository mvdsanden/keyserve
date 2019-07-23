// a_ksrvs_servicefactory.cpp                                         -*-c++-*-
#include <a_ksrvs_servicefactory.h>

#include <ksvc_configuration.h>
#include <a_ksrvs_grpcservice.h>

namespace MvdS {
namespace a_ksrvs {

namespace {

std::unique_ptr<ksvc::Service>
createService(ksvc::SecurityManager *    securityManager,
              const ksvc::ServiceConfig &config)
{
  if ("grpc" == config.type()) {
    return std::make_unique<GrpcService>(securityManager, config);
  }

  return nullptr;
}

} // anonymous namespace

// ---------------------
// Class: ServiceFactory
// ---------------------

// CREATORS
ServiceFactory::ServiceFactory(ksvc::SecurityManager *    securityManager,
                               const ksvc::Configuration &config)
  : d_securityManager(securityManager)
  , d_config(config)
{}

// MANIPULATORS
ServiceFactory::Services ServiceFactory::createConfigured()
{
  Services services;
  services.reserve(d_config.service().size());

  for (const auto &config : d_config.service()) {
    services.push_back(std::move(createService(d_securityManager, config)));
  }

  return std::move(services);
}

// MANIPULATORS

// ACCESSORS

} // namespace a_ksrvs
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
