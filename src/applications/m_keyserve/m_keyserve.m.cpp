// m_keyserve.m.cpp                                              -*-c++-*-
#include <iostream>

namespace {

  bool startAllServices(a_ksvc::ServiceFactory::Services* services)
  {
    size_t success = 0;

    for (auto &service : services) {
      success += service->start()?1:0;      
    }

    return 0 != success;
  }
  
} // anonymouse namespace

int main(int argc, char *argv[])
{
  ksrv::CommandlineArguments args;
  if (!ksrv::CommandlineArgumentsUtil::parse(argc, argv)) {
    return 1;
  }

  ksrv::Configuration config;
  if (!ksrv::ConfigurationUtil::readConfigurationFrom(&config, args)) {
    return 2;
  }

  a_kstore::KeyStoreFactory       keyStoreFactory(config);
  std::unique_ptr<ksrv::KeyStore> keyStore = keyStoreFactory.create();
  if (!keyStore) {
    return 3;
  }

  if (!keyStore.start()) {
    return 4;
  }

  ksrv::CachingKeyStore            cachingKeyStore(keyStore.get(), config);
  a_ksvc::ServiceFactory           serviceFactory(config);
  a_ksvc::ServiceFactory::Services services =
      serviceFactory.createConfigured(&services, &cachingKeyStore);

  if (!startAllServices(&services)) {
    LOG_ERR("No services started");
    return 6;
  }

  return 0;
}
