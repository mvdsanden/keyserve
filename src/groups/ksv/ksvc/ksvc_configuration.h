// ksvc_configuration.h                                               -*-c++-*-
// This file is auto generated, don't edit directly.
#include <kdadm_element.h>
#include <optional>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

namespace MvdS {
namespace ksvc {

// --------------------
// class KeyStoreConfig
// --------------------
class KeyStoreConfig
{
// DATA
std::string d_backend;
unsigned long long d_maxCachedObjects = 1000;
public:
// CREATORS
// MANIPULATOR
std::string& backend() { return d_backend;}
unsigned long long& maxCachedObjects() { return d_maxCachedObjects;}
// ACCESSORS
const std::string& backend() const { return d_backend;}
const unsigned long long& maxCachedObjects() const { return d_maxCachedObjects;}
}; // class KeyStoreConfig

// --- inline methods ---

// --------------------
// Class KeyStoreConfig
// --------------------

bool operator>>(const kdadm::Element &element, KeyStoreConfig& obj);
// ------------------
// class CryptoConfig
// ------------------
class CryptoConfig
{
// DATA
std::string d_backend = "dummy";
public:
// CREATORS
// MANIPULATOR
std::string& backend() { return d_backend;}
// ACCESSORS
const std::string& backend() const { return d_backend;}
}; // class CryptoConfig

// --- inline methods ---

// ------------------
// Class CryptoConfig
// ------------------

bool operator>>(const kdadm::Element &element, CryptoConfig& obj);
// -------------------
// class ServiceConfig
// -------------------
class ServiceConfig
{
// DATA
std::string d_type;
public:
// CREATORS
// MANIPULATOR
std::string& type() { return d_type;}
// ACCESSORS
const std::string& type() const { return d_type;}
}; // class ServiceConfig

// --- inline methods ---

// -------------------
// Class ServiceConfig
// -------------------

bool operator>>(const kdadm::Element &element, ServiceConfig& obj);
// -------------------
// class Configuration
// -------------------
class Configuration
{
// DATA
KeyStoreConfig d_keyStore;
CryptoConfig d_crypto;
std::vector<ServiceConfig> d_service;
public:
// CREATORS
// MANIPULATOR
KeyStoreConfig& keyStore() { return d_keyStore;}
CryptoConfig& crypto() { return d_crypto;}
std::vector<ServiceConfig>& service() { return d_service;}
// ACCESSORS
const KeyStoreConfig& keyStore() const { return d_keyStore;}
const CryptoConfig& crypto() const { return d_crypto;}
const std::vector<ServiceConfig>& service() const { return d_service;}
}; // class Configuration

// --- inline methods ---

// -------------------
// Class Configuration
// -------------------

bool operator>>(const kdadm::Element &element, Configuration& obj);
}; // namespace ksvc
}; // namespace MvdS
