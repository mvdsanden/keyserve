// kdadp_xmldocumentparser.h                                          -*-c++-*-
#ifndef INCLUDED_KDADP_XMLDOCUMENTPARSER
#define INCLUDED_KDADP_XMLDOCUMENTPARSER

#include <iosfwd>

namespace MvdS {

namespace kdadm {
class Document; // Forward declaration
}

namespace kdadp {

  
// ========================
// Class: XmlDocumentParser
// ========================

class XmlDocumentParser
{
  // ...

  // TYPES

  // DATA

  // PRIVATE MANIPULATORS

public:
  // CREATORS
  XmlDocumentParser();
  // ...

  // MANIPULATORS
  bool parse(kdadm::Document *document, std::istream& stream);
  // Parse the specified 'stream' into the specified 'document'. Return 'true'
  // on success.

  // ACCESSORS
};

} // namespace kdadp
} // namespace MvdS

#endif // INCLUDED_KDADP_XMLDOCUMENTPARSER

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
