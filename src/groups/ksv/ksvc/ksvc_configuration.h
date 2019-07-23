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
// class Configuration
// -------------------
class Configuration
{
// DATA
KeyStoreConfig d_keyStore;
CryptoConfig d_crypto;
public:
// CREATORS
// MANIPULATOR
KeyStoreConfig& keyStore() { return d_keyStore;}
CryptoConfig& crypto() { return d_crypto;}
// ACCESSORS
const KeyStoreConfig& keyStore() const { return d_keyStore;}
const CryptoConfig& crypto() const { return d_crypto;}
}; // class Configuration

// --- inline methods ---

// -------------------
// Class Configuration
// -------------------

bool operator>>(const kdadm::Element &element, Configuration& obj);
}; // namespace ksvc
}; // namespace MvdS
