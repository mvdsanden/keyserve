// kdadm_element.h                                                    -*-c++-*-
#ifndef INCLUDED_KDADM_ELEMENT
#define INCLUDED_KDADM_ELEMENT

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <charconv>

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
  typedef std::vector<std::shared_ptr<Element>> Children;

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
  Children    d_children;

  // PRIVATE MANIPULATORS

public:
  // CREATORS

  // MANIPULATORS
  void setTag(const std::string& tag);
  // Set the tag name of the element. Behavior is undefined if 'setValue()' was
  // called before this call.

  void setValue(const std::string& value);
  // Set the value of the element. Behavior is undefined if 'setTag()' was
  // called before this call.

  Children& children();
  // Return all children.
  
  // ACCESSORS
  bool isValueType() const;
  // Return 'true' iff this is a value type element.

  bool isElementType() const;
  // Return 'true' iff this is an element type element.
  
  const std::string& tag() const;
  // Return the tag name of the element. Behavior is undefined unless
  // 'isValueType() == false'.

  template <class T>
  T as() const;
  // Return the value of the element converted to the specified type 'T'.
  // Behavior is undefined unless 'isValueType() == true'.

  const Children& children() const;
  // Return all children.

  void getElementsByTagName(Children *elements, const std::string &tag);
  // Finds all children with the specified 'tag' and adds those to the specified
  // 'elements'.
};

  // --- INLINE METHODS ---

// --------------
// Class: Element
// --------------

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

inline Element::Children &Element::children()
{
  return d_children;
}

// ACCESSORS
inline bool Element::isValueType() const { return d_type == e_ValueType; }

inline bool Element::isElementType() const { return d_type == e_ElementType; }

inline const std::string &Element::tag() const { return d_data; }

template <class T>
inline T Element::as() const
{
  T value;
  std::from_chars(d_data.c_str(), d_data.c_str() + d_data.size(), value);
  return value;
}

inline const Element::Children &Element::children() const { return d_children; }

inline void Element::getElementsByTagName(Children *         elements,
                                          const std::string &tag)
{
  std::copy_if(
      std::begin(d_children),
      std::end(d_children),
      std::back_inserter(*elements),
      [tag](const auto &e) { return e->isElementType() && tag == e->tag(); });
}

} // namespace kdadm
} // namespace MvdS

#endif // INCLUDED_KDADM_ELEMENT

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
