// m_keyserve.m.cpp                                              -*-c++-*-
#include <ksvc_commandlineargs.h>
// #include <ksrc_configuration.h>
// #include <a_kstores_keystorefactory.h>
// #include <ksrv_cachingkeystore.h>
// #include <ksrv_servicefactory.h>
// #include <a_ksrvs_servicefactory.h>

#include <iostream>
#include <memory>

using namespace MvdS;

namespace {

  // bool startAllServices(ksrv::ServiceFactory::Services* services)
  // {
  //   size_t success = 0;

  //   for (auto &service : services) {
  //     success += service->start()?1:0;      
  //   }

  //   return 0 != success;
  // }
  
} // anonymouse namespace

int main(int argc, char *argv[])
{
  ksvc::CommandlineArgs args;
  // if (!ksvc::CommandlineArgsUtil::parse(&args, argc, argv)) {
  //   ksvc::CommandLineArgumentsUtil::printUsage(argc, argv);
  //   return 1;
  // }

  // ksrv::Configuration config;
  // if (!ksrv::ConfigurationUtil::readConfiguration(&config, args)) {
  //   return 2;
  // }

  // a_kstores::KeyStoreFactory      keyStoreFactory(config);
  // std::unique_ptr<ksrv::KeyStore> keyStore = keyStoreFactory.create();
  // if (!keyStore) {
  //   return 3;
  // }

  // if (!keyStore.start()) {
  //   return 4;
  // }

  // ksrv::CachingKeyStore cachingKeyStore(keyStore.get(), config);

  // a_ksvcs::ServiceFactory        serviceFactory(config);
  // ksrv::ServiceFactory::Services services =
  //     serviceFactory.createConfigured(&services, &cachingKeyStore);

  // if (!startAllServices(&services)) {
  //   LOG_ERR("No services started");
  //   return 6;
  // }

  return 0;
}
