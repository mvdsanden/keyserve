// ksvc_configurationutil.cpp                                         -*-c++-*-
#include <ksvc_configurationutil.h>
#include <ksvc_configuration.h>
#include <ksvc_commandlineargs.h>

#include <kdadm_document.h>
#include <kdadp_xmldocumentparser.h>

#include <fstream>
#include <spdlog/spdlog.h>

namespace MvdS {
namespace ksvc {

// ------------------------
// Class: ConfigurationUtil
// ------------------------

  // CLASS METHODS
bool ConfigurationUtil::readConfiguration(Configuration *        config,
                                          const CommandlineArgs &args)
{
  std::string filename = "config.xml";
  
  if (!args.configFiles().empty()) {
    filename = args.configFiles().back();
  }
  
  kdadm::Document document;

  {
    kdadp::XmlDocumentParser parser;

    std::ifstream stream(filename);
    if (!stream) {
      spdlog::error("Could not open config file: {}", filename);
      return false;
    }
    
    if (!parser.parse(&document, stream, filename)) {
      return false;
    }    
  }

  auto root = document.root();
  if (!root) {
    spdlog::error("No root node in config file: {}", filename);
    return false;
  }
  
  return *(root) >> *config;  
}

// CREATORS

// MANIPULATORS

// ACCESSORS

} // namespace ksvc
} // namespace MvdS

// ----------------------------------------------------------------------------
// Copyright (C) 2018 Marten van de Sanden
// ----------------------------------------------------------------------------
