// kdadm_element.h                                                    -*-c++-*-
#ifndef INCLUDED_KDADM_ELEMENT
#define INCLUDED_KDADM_ELEMENT

#include <memory>
#include <string>
#include <vector>
#include <algorithm>

namespace MvdS {
namespace kdadm {

// ==============
// Class: Element
// ==============

class Element
{
  // ...

public:
  // PUBLIC TYPES
  typedef std::vector<std::shared_ptr<Element>> Elements;

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

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  static std::unique_ptr<Element> createElement(const std::string& tag);
  // Return a newly created element type element with the specified 'tag'.

  static std::unique_ptr<Element> createValue(const std::string& value);
  // Return a newly created value type element with the specified 'value'.
  
  // MANIPULATORS
  void setTag(const std::string& tag);
  // Set the tag name of the element. Behavior is undefined if 'setValue()' was
  // called before this call.

  void setValue(const std::string& value);
  // Set the value of the element. Behavior is undefined if 'setTag()' was
  // called before this call.

  Elements& children();
  // Return all children.
  
  // ACCESSORS
  bool isValueType() const;
  // Return 'true' iff this is a value type element.

  bool isElementType() const;
  // Return 'true' iff this is an element type element.
  
  const std::string& tag() const;
  // Return the tag name of the element. Behavior is undefined unless
  // 'isValueType() == false'.

  const std::string& value() const;
  // Return the satring value of the elemen. Behavior is undefined unless
  // 'isValueType() == true'.

  const Elements& children() const;
  // Return all children.

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
inline std::unique_ptr<Element> Element::createElement(const std::string &tag)
{
  std::unique_ptr<Element> element(new Element);
  element->setTag(tag);
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

// ACCESSORS
inline bool Element::isValueType() const { return d_type == e_ValueType; }

inline bool Element::isElementType() const { return d_type == e_ElementType; }

inline const std::string &Element::tag() const { return d_data; }

inline const std::string &Element::value() const { return d_data; }

inline const Element::Elements &Element::children() const { return d_children; }

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
