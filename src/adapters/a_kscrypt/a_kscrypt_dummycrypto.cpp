// a_kscrypt_dummycrypto.cpp                                          -*-c++-*-
#include <a_kscrypt_dummycrypto.h>

#include <ksvc_configuration.h>

#include <ksvc_cryptokeyversion.pb.h>
#include <ksvc_cryptokeyversiontemplate.pb.h>

#include <google/protobuf/util/time_util.h>

namespace MvdS {
namespace a_kscrypt {

// ------------------
// Class: DummyCrypto
// ------------------

// CREATORS
DummyCrypto::DummyCrypto(const ksvc::CryptoConfig &config) {}

// MANIPULATORS
void DummyCrypto::createCryptoKey(
    ksvc::ResultFunction<std::shared_ptr<ksvc::CryptoKeyVersion>> result,
    ksvc::CryptoKeyVersionTemplate versionTemplate)
{
  using TimeUtil = google::protobuf::util::TimeUtil;
  
  auto version = std::make_shared<ksvc::CryptoKeyVersion>();
  version->set_algorithm(versionTemplate.algorithm());
  version->set_createtime(TimeUtil::ToString(TimeUtil::GetCurrentTime()));

  result(ksvc::ResultStatus::e_success, std::move(version));
}

// ACCESSORS

} // namespace a_kscrypt
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
