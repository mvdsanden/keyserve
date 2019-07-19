// a_kstor_memorykeystore.t.cpp                                       -*-c++-*-
#include <a_kstor_memorykeystore.h>

#include <ksvc_configuration.h>

#include <ksvc_keyring.pb.h>
#include <ksvc_cryptokey.pb.h>

#include <gtest/gtest.h>

using namespace MvdS;
using namespace MvdS::a_kstor;

TEST(MemoryKeyStoreTest, Constructor)
{
  // TEST CONSTRUCTOR
  //
  // Concern:
  //   The objects constructor should work.
  //
  // Test plan:
  //   Construct the object.
  ksvc::KeyStoreConfig config;
  MemoryKeyStore obj(config);
}

TEST(MemoryKeyStoreTest, createKeyRing)
{
  ksvc::KeyStoreConfig config;
  MemoryKeyStore obj(config);

  std::string   parent = "projects/test/locations/A/keyRings";
  std::string   id     = "test";
  std::string   name   = parent + "/" + id;

  ksvc::KeyRing keyRing;
  keyRing.set_name(name);

  obj.createKeyRing(
      [&](auto status, auto object) {
        ASSERT_EQ(status, ksvc::ResultStatus::e_success);
        ASSERT_EQ(object->name(), name);
      },
      parent,
      id,
      keyRing);

  obj.createKeyRing(
      [&](auto status, auto object) {
        ASSERT_EQ(status, ksvc::ResultStatus::e_exists);
      },
      parent,
      id,
      keyRing);
}

TEST(MemoryKeyStoreTest, createCryptoKey)
{
  ksvc::KeyStoreConfig config;
  MemoryKeyStore obj(config);

  std::string   parent = "projects/test/locations/A/cryptoKeys";
  std::string   id     = "test";
  std::string   name   = parent + "/" + id;

  ksvc::CryptoKey cryptoKey;
  cryptoKey.set_name(name);

  obj.createCryptoKey(
      [&](auto status, auto object) {
        ASSERT_EQ(status, ksvc::ResultStatus::e_success);
        ASSERT_EQ(object->name(), name);
      },
      parent,
      id,
      cryptoKey);

  obj.createCryptoKey(
      [&](auto status, auto object) {
        ASSERT_EQ(status, ksvc::ResultStatus::e_exists);
      },
      parent,
      id,
      cryptoKey);
}

TEST(MemoryKeyStoreTest, getKeyRing)
{
  ksvc::KeyStoreConfig config;
  MemoryKeyStore obj(config);

  std::string parent = "projects/test/locations/A/keyRings";
  std::string id     = "test";
  std::string name   = parent + "/" + id;

  ksvc::KeyRing keyRing;
  keyRing.set_name(name);

  obj.getKeyRing(
      [&](auto status, auto object) {
        ASSERT_EQ(status, ksvc::ResultStatus::e_notFound);
      },
      name);
  
  obj.createKeyRing(
      [&](auto status, auto object) {
        ASSERT_EQ(status, ksvc::ResultStatus::e_success);
        ASSERT_EQ(object->name(), name);
      },
      parent,
      id,
      keyRing);

  obj.getKeyRing(
      [&](auto status, auto object) {
        ASSERT_EQ(status, ksvc::ResultStatus::e_success);
      },
      name);
}

TEST(MemoryKeyStoreTest, getCryptoKey)
{
  ksvc::KeyStoreConfig config;
  MemoryKeyStore obj(config);

  std::string parent = "projects/test/locations/A/cryptoKeys";
  std::string id     = "test";
  std::string name   = parent + "/" + id;

  ksvc::CryptoKey cryptoKey;
  cryptoKey.set_name(name);

  obj.getCryptoKey(
      [&](auto status, auto object) {
        ASSERT_EQ(status, ksvc::ResultStatus::e_notFound);
      },
      name);
  
  obj.createCryptoKey(
      [&](auto status, auto object) {
        ASSERT_EQ(status, ksvc::ResultStatus::e_success);
        ASSERT_EQ(object->name(), name);
      },
      parent,
      id,
      cryptoKey);

  obj.getCryptoKey(
      [&](auto status, auto object) {
        ASSERT_EQ(status, ksvc::ResultStatus::e_success);
      },
      name);
}



int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
