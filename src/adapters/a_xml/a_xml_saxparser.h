// a_xml_saxparser.h                                                  -*-c++-*-
#ifndef INCLUDED_A_XML_SAXPARSER
#define INCLUDED_A_XML_SAXPARSER

#include <kdadp_saxparser.h>

namespace MvdS {
namespace a_xml {

// ================
// Class: SaxParser
// ================

class SaxParser : public kdadp::SaxParser
{
  // ...

  // TYPES

  // DATA
  kdadp::SaxDocumentHandler *d_documentHandler;
  
  // PRIVATE MANIPULATORS

public:
  // CREATORS

  // MANIPULATORS
  void setDocumentHandler(kdadp::SaxDocumentHandler *documentHandler) override;
  // Set the specified 'documentHandler' to be used for parsing.
  
  virtual bool parse(const gsl::span<char>& data) override;
  // Parse the specified 'data'. Return 'true' on success.
  
  virtual bool parse(std::istream& stream) override;
  // Parse the specified 'stream'. Return 'true' on success.

  // ACCESSORS
};

} // namespace a_xml
} // namespace MvdS

#endif // INCLUDED_A_XML_SAXPARSER

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
