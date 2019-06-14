// kdadp_saxparser.h                                                  -*-c++-*-
#ifndef INCLUDED_KDADP_SAXPARSER
#define INCLUDED_KDADP_SAXPARSER

#include <string>
#include <utility>

#include <gsl/span>

namespace MvdS {
namespace kdadp {

// =========================
// Class: SaxDocumentHandler
// =========================
struct SaxDocumentHandler
{
  typedef std::pair<std::string, std::string> Attribute;
  typedef gsl::span<Attribute>                Attributes;

  virtual void startDocument() = 0;
  // Called at the start of a document.

  virtual void startElement(const std::string& name, const Attributes& attributes) = 0;
  // Called at the start of every element.

  virtual void characterData(const std::string& data) = 0;
  // Called for character data.

  virtual void comment(const std::string& data) = 0;
  
  virtual void endElement(const std::string& name) = 0;
  // Called at the end of every element.

  virtual void endDocument() = 0;
  // Called at the end of a document.
};
  
// ================
// Class: SaxParser
// ================

class SaxParser
{
  // ...

  // TYPES

  // DATA

  // PRIVATE MANIPULATORS

public:
  // CREATORS

  // MANIPULATORS
  virtual void setDocumentHandler(SaxDocumentHandler *documentHandler) = 0;
  // Set the specified 'documentHandler' to be used for parsing.
  
  virtual bool parse(const gsl::span<char>& data) = 0;
  // Parse the specified 'data'. Return 'true' on success.
  
  virtual bool parse(std::istream& stream) = 0;
  // Parse the specified 'stream'. Return 'true' on success.

  // ACCESSORS
};

} // namespace kdadp
} // namespace MvdS

#endif // INCLUDED_KDADP_SAXPARSER

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
