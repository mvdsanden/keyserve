// m_test_configuration.cpp                                           -*-c++-*-
#include <m_test_configuration.h>
#include <spdlog/fmt/bundled/ostream.h>

namespace MvdS {
namespace m_test {

bool operator>>(const kdadm::Element &element, Note& obj)
{
  { // BEGIN to
    auto iter = kdadm::ElementUtils::getElementByTagName(
      "to",
      element.children().begin(),
      element.children().end());

    if (iter == element.children().end()) {
      spdlog::error("{}: expected element '{}'",
        element.location(), "to");
      return false;
    }

    if (!(**iter >> obj.to())) {
      spdlog::error("{}: expected xs:string value", (*iter)->location());
      return false;
    }
  } // END to

  { // BEGIN from
    auto iter = kdadm::ElementUtils::getElementByTagName(
      "from",
      element.children().begin(),
      element.children().end());

    if (iter == element.children().end()) {
      spdlog::error("{}: expected element '{}'",
        element.location(), "from");
      return false;
    }

    if (!(**iter >> obj.from())) {
      spdlog::error("{}: expected xs:string value", (*iter)->location());
      return false;
    }
  } // END from

  { // BEGIN heading
    auto iter = kdadm::ElementUtils::getElementByTagName(
      "heading",
      element.children().begin(),
      element.children().end());

    if (iter == element.children().end()) {
      return true;
    }

    if (!(**iter >> obj.heading().emplace())) {
      spdlog::error("{}: expected xs:string value", (*iter)->location());
      return false;
    }
  } // END heading

  { // BEGIN body
    bool success = true;
    element.getElementsByTagName(
      "body",
      [&obj, &success](const auto& e){
        success = success && (*e >> obj.body().emplace_back());
      });

    if (!success) {
      return false;
    }

    if (1 > obj.body().size()) {
      spdlog::error("{}: expected at least 1 elements with name 'body'",
        element.location());
    }
  } // END body

  { // BEGIN count
    auto iter = kdadm::ElementUtils::getElementByTagName(
      "count",
      element.children().begin(),
      element.children().end());

    if (iter == element.children().end()) {
      spdlog::error("{}: expected element '{}'",
        element.location(), "count");
      return false;
    }

    if (!(**iter >> obj.count())) {
      spdlog::error("{}: expected xs:integer value", (*iter)->location());
      return false;
    }
  } // END count

  return true;
}
}; // namespace m_test
}; // namespace MvdS
