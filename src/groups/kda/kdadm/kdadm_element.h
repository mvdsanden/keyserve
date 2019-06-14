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
  typedef gsl::span<Attribute>                  AttributeSpan;

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

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  static std::unique_ptr<Element>
  createElement(const std::string &tag, const AttributeSpan &attributes = AttributeSpan());
  // Return a newly created element type element with the specified 'tag' and
  // optionally the specified 'attributes'.

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

  template <class OutputIt>
  void getElementsByTagName(OutputIt outputIt, const std::string &tag);
  // Finds all children with the specified 'tag' output those using the
  // specified 'outputIterator'.
};

  // --- INLINE METHODS ---

// --------------
// Class: Element
// --------------

// CREATORS
inline std::unique_ptr<Element>
Element::createElement(const std::string &tag, const AttributeSpan &attributes)
{
  std::unique_ptr<Element> element(new Element);
  element->setTag(tag);
  element->attributes().insert(element->attributes().end(), std::begin(attributes), std::end(attributes));
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

template <class OutputIt>
inline void Element::getElementsByTagName(OutputIt           outputIt,
                                          const std::string &tag)
{
  std::copy_if(
      std::begin(d_children),
      std::end(d_children),
      outputIt,
      [tag](const auto &e) { return e->isElementType() && tag == e->tag(); });
}

} // namespace kdadm
} // namespace MvdS

#endif // INCLUDED_KDADM_ELEMENT

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
