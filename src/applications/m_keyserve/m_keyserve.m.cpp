// m_keyserve.m.cpp                                              -*-c++-*-
#include <a_kscrypt_cryptofactory.h>
#include <a_kstor_keystorefactory.h>
#include <ksvc_cachingkeystore.h>
#include <ksvc_commandlineargs.h>
#include <ksvc_configuration.h>
#include <ksvc_configurationutil.h>
#include <ksvc_crypto.h>
#include <ksvc_keystore.h>
#include <ksvc_keymanager.h>
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
  ksvc::CommandlineArgs arguments;
  ksvc::CommandlineArgsUtil::parse(&arguments, {argv, argc});

  if (arguments.printUsage()) {
    ksvc::CommandlineArgsUtil::printUsage(&std::cout, {argv, argc});
    return 1;
  }

  ksvc::Configuration config;
  if (!ksvc::ConfigurationUtil::readConfiguration(&config, arguments)) {
    return 2;
  }

  a_kstor::KeyStoreFactory        keyStoreFactory(config.keyStore());
  std::unique_ptr<ksvc::KeyStore> keyStore = keyStoreFactory.create();
  if (!keyStore) {
    return 3;
  }

  // if (!keyStore.start()) {
  //   return 4;
  // }

  a_kscrypt::CryptoFactory     cryptoFactory(config.crypto());
  std::unique_ptr<ksvc::Crypto> crypto = cryptoFactory.create();
  if (!crypto) {
    return 5;
  }

  // if (!crypto.start()) {
  //   return 6;
  // }

  ksvc::CachingKeyStore cachingKeyStore(keyStore.get(), config.keyStore());

  std::unique_ptr<ksvc::KeyManager> keyManager(
      ksvc::KeyManager::create(&cachingKeyStore, crypto.get(), config));

  // ksrv::SecuredKeyManager securedKeyManager(&keyManager, config);
  // // - SecuredKeyManager friends SecurityManager so that it can only access KeyManagerSessions (private: SecuredKeyManager::createSession(domains...)?)?
  // // - SecuredKeyManagerSessions are wrappers around KeyManager that perform access checks.


  // ksrv::SecurityManager securityManager(&securedKeyManager, config);

  // // Service sessions should get access to the key manager by entering a secure
  // // session through the security manager!!
  // a_ksvcs::ServiceFactory        serviceFactory(&securityManager, config);
  // ksrv::ServiceFactory::Services services;
  // serviceFactory.createConfigured(&services);

  // if (!startAllServices(&services)) {
  //   LOG_ERR("No services started");
  //   return 7;
  // }

  return 0;
}
