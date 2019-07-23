// a_ksrvs_grpcservice.cpp                                            -*-c++-*-
#include <a_ksrvs_grpcservice.h>

namespace MvdS {
namespace a_ksrvs {

// ------------------
// Class: GrpcService
// ------------------

// CREATORS
GrpcService::GrpcService(ksvc::SecurityManager *    securityManager,
                         const ksvc::ServiceConfig &config)
    : d_securityManager(securityManager)
{}

GrpcService::~GrpcService() {}

// MANIPULATORS
void GrpcService::start()
{
}

void GrpcService::stop()
{
}

// MANIPULATORS

// ACCESSORS

} // namespace a_ksrvs
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
