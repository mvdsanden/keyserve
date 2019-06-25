// m_test_configuration.h                                             -*-c++-*-
#include <kdadm_element.h>
#include <optional>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

namespace MvdS {
namespace m_test {

// ----------
// class Note
// ----------
class Note
{
// DATA
std::string d_to;
std::string d_from;
std::optional<std::string> d_heading;
std::vector<std::string> d_body;
public:
// CREATORS
// MANIPULATOR
std::string& to() { return d_to;}
std::string& from() { return d_from;}
std::optional<std::string>& heading() { return d_heading;}
std::vector<std::string>& body() { return d_body;}
// ACCESSORS
const std::string& to() const { return d_to;}
const std::string& from() const { return d_from;}
const std::optional<std::string>& heading() const { return d_heading;}
const std::vector<std::string>& body() const { return d_body;}
}; // class Note

// --- inline methods ---

// ----------
// Class Note
// ----------

bool operator>>(const kdadm::Element &element, Note& obj);
}; // namespace m_test
}; // namespace MvdS
