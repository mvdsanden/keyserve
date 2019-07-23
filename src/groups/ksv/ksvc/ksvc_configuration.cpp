// ksvc_configuration.cpp                                             -*-c++-*-
// This file is auto generated, don't edit directly.
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
bool operator>>(const kdadm::Element &element, CryptoConfig& obj)
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

  return true;
}
bool operator>>(const kdadm::Element &element, ServiceConfig& obj)
{
  { // BEGIN type
    auto iter = kdadm::ElementUtils::getElementByTagName(
      "type",
      element.children().begin(),
      element.children().end());

    if (iter == element.children().end()) {
      spdlog::error("{}: expected element '{}'",
        element.location(), "type");
      return false;
    }

    if (!(**iter >> obj.type())) {
      spdlog::error("{}: expected xs:string value", (*iter)->location());
      return false;
    }
  } // END type

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

  { // BEGIN crypto
    auto iter = kdadm::ElementUtils::getElementByTagName(
      "crypto",
      element.children().begin(),
      element.children().end());

    if (iter == element.children().end()) {
      spdlog::error("{}: expected element '{}'",
        element.location(), "crypto");
      return false;
    }

    if (!(**iter >> obj.crypto())) {
      spdlog::error("{}: expected CryptoConfig value", (*iter)->location());
      return false;
    }
  } // END crypto

  { // BEGIN service
    bool success = true;
    element.getElementsByTagName(
      "service",
      [&obj, &success](const auto& e){
        success = success && (*e >> obj.service().emplace_back());
      });

    if (!success) {
      return false;
    }

    if (1 > obj.service().size()) {
      spdlog::error("{}: expected at least 1 elements with name 'service'",
        element.location());
    }
  } // END service

  return true;
}
}; // namespace ksvc
}; // namespace MvdS
