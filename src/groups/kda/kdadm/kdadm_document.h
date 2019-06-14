// kdadm_document.h                                                   -*-c++-*-
#ifndef INCLUDED_KDADM_DOCUMENT
#define INCLUDED_KDADM_DOCUMENT

#include <memory>

namespace MvdS {
namespace kdadm {

class Element; // Forward declaration.
  
// ===============
// Class: Document
// ===============

class Document
{
  // Provides a document for a simplified DOM.
  //
  // A document is basically a tree of elements.

  // TYPES

  // DATA
  std::shared_ptr<Element> d_root;

  // PRIVATE MANIPULATORS

public:
  // CREATORS

  // MANIPULATORS
  void setRoot(std::shared_ptr<Element> element);
  // Set document root to the specified 'element'.

  // ACCESSORS
  std::shared_ptr<Element> root() const;
  // Return document root element.
};

// --- INLINE METHODS ---

// ---------------
// Class: Document
// ---------------

// MANIPULATORS
inline void Document::setRoot(std::shared_ptr<Element> element)
{
  d_root = std::move(element);
}

// ACCESSORS
inline std::shared_ptr<Element> Document::root() const
{
  return d_root;
}


} // namespace kdadm
} // namespace MvdS

#endif // INCLUDED_KDADM_DOCUMENT

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
