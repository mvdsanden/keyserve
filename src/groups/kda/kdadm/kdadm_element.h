// kdadm_element.h                                                    -*-c++-*-
#ifndef INCLUDED_KDADM_ELEMENT
#define INCLUDED_KDADM_ELEMENT

#include <algorithm>
#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include <gsl/span>

namespace MvdS {
namespace kdadm {

// ==============
// Class: Element
// ==============

class Element
{
  // Provides a document element for a simplified DOM.
  //
  // There are two types of elements:
  // * ElementType: contains a tag.
  // * ValueType: contains a string.

public:
  // PUBLIC TYPES
  typedef std::vector<std::shared_ptr<Element>> Elements;
  typedef std::pair<std::string, std::string>   Attribute;
  typedef std::vector<Attribute>                Attributes;

  struct Location {
    std::shared_ptr<std::string> d_sourceName;
    std::pair<size_t, size_t>    d_lineNumbers;
    std::pair<size_t, size_t>    d_columnNumbers;
  };

private:
  
  // TYPES
  enum Type
  {
    e_UndefinedType = 0,
    e_ElementType   = 1,
    e_ValueType     = 2
  };

  // DATA
  Type        d_type = e_UndefinedType;
  std::string d_data;
  Elements    d_children;
  Attributes  d_attributes;
  Location    d_location;

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  static std::unique_ptr<Element>
  createElement(const std::string &tag);
  // Return a newly created element type element with the specified 'tag'.

  template <class Iter>
  static std::unique_ptr<Element>
  createElement(const std::string &tag, Iter beginAttributes, Iter endAttributes);
  // Return a newly created element type element with the specified 'tag' and
  // set the attributes from the range of the specified 'beginAttributes' and
  // 'endAttributes'.

  static std::unique_ptr<Element> createValue(const std::string& value);
  // Return a newly created value type element with the specified 'value'.
  
  // MANIPULATORS
  void setTag(const std::string& tag);
  // Set the tag name of the element. This implicitly makes this an element type
  // element. Behavior is undefined if 'setValue()' was called before this call.

  void setValue(const std::string& value);
  // Set the value of the element. This implicitly makes this a value type
  // element. Behavior is undefined if 'setTag()' was called before this call.

  Elements& children();
  // Return all children. Behavior is undefined unless 'isElementType() ==
  // true'.

  Attributes& attributes();
  // Return all attributes.

  Location& location();
  // Return the element file location.
  
  // ACCESSORS
  bool isValueType() const;
  // Return 'true' iff this is a value type element.

  bool isElementType() const;
  // Return 'true' iff this is an element type element.
  
  const std::string& tag() const;
  // Return the tag name of the element. Behavior is undefined unless
  // 'isElementType() == true'.

  const std::string& value() const;
  // Return the satring value of the elemen. Behavior is undefined unless
  // 'isValueType() == true'.

  const Elements& children() const;
  // Return all children.

  const Attributes& attributes() const;
  // Return all attributes. Behavior is undefined unless 'isElementType() ==
  // true'.

  const Location& location() const;
  // Return the element file location.

  template <class OutputIt>
  void getElementsByTagName(const OutputIt &   outputIt,
                            const std::string &tag) const;
  // Finds all children with the specified 'tag' output those using the
  // specified 'outputIterator'.

  Attributes::const_iterator
  getFirstAttributeByName(const std::string &name) const;
  // Return the first attribute with the specified 'name' or
  // 'attributes().end()' if not found.
};

// ===================
// Struct ElementUtils
// ===================

struct ElementUtils
{
  // TYPES
  typedef Element::Elements   Elements;
  typedef Element::Attributes Attributes;

  // CLASS METHODS
  template <class Iter>
  static Iter getElementByTagName(const std::string &tag, Iter begin, Iter end);
  // Find the first element with the specified 'tag' in the specified 'begin'
  // and the specified 'end' range.
  
  template <class Iter>
  static Iter getAttributeByName(const std::string &name, Iter begin, Iter end);
  // Find the first attribute with the specified 'name' in the specified 'begin'
  // and the specified 'end' range.  
};

// --- INLINE METHODS ---

// --------------
// Class: Element
// --------------

// CREATORS
inline std::unique_ptr<Element>
Element::createElement(const std::string &tag)
{
  std::unique_ptr<Element> element(new Element);
  element->setTag(tag);
  return std::move(element);
}

template <class Iter>
inline std::unique_ptr<Element>
Element::createElement(const std::string &tag, Iter beginAttributes, Iter endAttributes)
{
  std::unique_ptr<Element> element(new Element);
  element->setTag(tag);
  element->attributes().insert(element->attributes().end(), beginAttributes, endAttributes);
  return std::move(element);  
}

inline std::unique_ptr<Element> Element::createValue(const std::string &value)
{
  std::unique_ptr<Element> element(new Element);
  element->setValue(value);
  return std::move(element);
}

// MANIPULATORS
inline void Element::setTag(const std::string &tag)
{
  d_type = e_ElementType;
  d_data = tag;
}

inline void Element::setValue(const std::string &value)
{
  d_type = e_ValueType;
  d_data = value;
}

inline Element::Elements &Element::children()
{
  return d_children;
}

inline Element::Attributes &Element::attributes() { return d_attributes; }

inline Element::Location& Element::location() { return d_location; }

// ACCESSORS
inline bool Element::isValueType() const { return d_type == e_ValueType; }

inline bool Element::isElementType() const { return d_type == e_ElementType; }

inline const std::string &Element::tag() const
{
  assert(isElementType());
  return d_data;
}

inline const std::string &Element::value() const {
  assert(isValueType());
  return d_data;
}

inline const Element::Elements &Element::children() const { return d_children; }

inline const Element::Attributes &Element::attributes() const
{
  return d_attributes;
}

inline const Element::Location &Element::location() const { return d_location; }

template <class OutputIt>
inline void Element::getElementsByTagName(const OutputIt &   outputIt,
                                          const std::string &tag) const
{
  std::copy_if(
      std::begin(d_children),
      std::end(d_children),
      outputIt,
      [tag](const auto &e) { return e->isElementType() && tag == e->tag(); });
}

inline Element::Attributes::const_iterator
Element::getFirstAttributeByName(const std::string &name) const
{
  return ElementUtils::getAttributeByName(
      name, attributes().begin(), attributes().end());
}

// -------------------
// Struct ElementUtils
// -------------------

// CLASS METHODS
template <class Iter>
inline Iter ElementUtils::getElementByTagName(const std::string &tag, Iter begin, Iter end)
{
  return std::find_if(begin, end, [tag](const auto &e) {
    return e->isElementType() && tag == e->tag();
  });
}

template <class Iter>
inline Iter ElementUtils::getAttributeByName(const std::string &name, Iter begin, Iter end)
{
  return std::find_if(
      begin, end, [name](const auto &e) { return e.first == name; });
}

inline std::ostream &operator<<(std::ostream& stream, const Element::Location& location)
{
  if (location.d_sourceName) {
    stream << *location.d_sourceName.get() << ":";
  }

  stream << location.d_lineNumbers.second << ":";
  return stream;
}
  
} // namespace kdadm
} // namespace MvdS

#endif // INCLUDED_KDADM_ELEMENT

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
