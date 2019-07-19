// ksvc_configuration.cpp                                             -*-c++-*-
#include <ksvc_configuration.h>
#include <spdlog/fmt/bundled/ostream.h>

namespace MvdS {
namespace ksvc {

bool operator>>(const kdadm::Element &element, KeyStoreConfig& obj)
{
  { // BEGIN backend
    auto iter = kdadm::ElementUtils::getElementByTagName(
      "backend",
      element.children().begin(),
      element.children().end());

    if (iter == element.children().end()) {
      spdlog::error("{}: expected element '{}'",
        element.location(), "backend");
      return false;
    }

    if (!(**iter >> obj.backend())) {
      spdlog::error("{}: expected xs:string value", (*iter)->location());
      return false;
    }
  } // END backend

  { // BEGIN maxCachedObjects
    auto iter = kdadm::ElementUtils::getElementByTagName(
      "maxCachedObjects",
      element.children().begin(),
      element.children().end());

    if (iter == element.children().end()) {
      spdlog::error("{}: expected element '{}'",
        element.location(), "maxCachedObjects");
      return false;
    }

    if (!(**iter >> obj.maxCachedObjects())) {
      spdlog::error("{}: expected xs:unsigned value", (*iter)->location());
      return false;
    }
  } // END maxCachedObjects

  return true;
}
bool operator>>(const kdadm::Element &element, Configuration& obj)
{
  { // BEGIN keyStore
    auto iter = kdadm::ElementUtils::getElementByTagName(
      "keyStore",
      element.children().begin(),
      element.children().end());

    if (iter == element.children().end()) {
      spdlog::error("{}: expected element '{}'",
        element.location(), "keyStore");
      return false;
    }

    if (!(**iter >> obj.keyStore())) {
      spdlog::error("{}: expected KeyStoreConfig value", (*iter)->location());
      return false;
    }
  } // END keyStore

  return true;
}
}; // namespace ksvc
}; // namespace MvdS
