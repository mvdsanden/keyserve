// ksvc_configuration.h                                               -*-c++-*-
#include <kdadm_element.h>
#include <optional>
#include <spdlog/spdlog.h>
#include <vector>

namespace MvdS {
namespace ksvc {

// --------------------
// class KeyStoreConfig
// --------------------
class KeyStoreConfig
{
// DATA
public:
// CREATORS
// MANIPULATOR
// ACCESSORS
}; // class KeyStoreConfig

// --- inline methods ---

// --------------------
// Class KeyStoreConfig
// --------------------

bool operator>>(const kdadm::Element &element, KeyStoreConfig& obj);
// -------------------
// class Configuration
// -------------------
class Configuration
{
// DATA
KeyStoreConfig d_keyStore;
public:
// CREATORS
// MANIPULATOR
KeyStoreConfig& keyStore() { return d_keyStore;}
// ACCESSORS
const KeyStoreConfig& keyStore() const { return d_keyStore;}
}; // class Configuration

// --- inline methods ---

// -------------------
// Class Configuration
// -------------------

bool operator>>(const kdadm::Element &element, Configuration& obj);
}; // namespace ksvc
}; // namespace MvdS
