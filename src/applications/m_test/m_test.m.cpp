// m_test.m.cpp                                              -*-c++-*-
#include <iostream>
#include <fstream>

#include <m_test_configuration.h>

#include <kdadm_document.h>
#include <kdadp_xmldocumentparser.h>

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>

using namespace MvdS;
using namespace MvdS::m_test;

namespace {

    struct Logger {

    std::shared_ptr<spdlog::logger> d_logger;
    
    Logger()      
    {

      d_logger = spdlog::basic_logger_mt<spdlog::async_factory>("logger", "test.log");
      spdlog::set_default_logger(d_logger);
      spdlog::set_level(spdlog::level::debug);
    }

    ~Logger()
    {
    }

  };

}; // anonymous namespace

int main(int argc, char *argv[])
{

  Logger logger;
  spdlog::info("Init: {}", argv[0]);
  
  kdadm::Document document;

  {
    kdadp::XmlDocumentParser parser;

    std::ifstream stream("config.xml");
    if (!stream) {
      spdlog::error("Could not open config file.");
      return 1;
    }
    
    if (!parser.parse(&document, stream, "config.xml")) {
      return 2;
    }    
  }

  auto root = document.root();
  if (!root) {
    spdlog::error("No root node.");
    return 3;
  }
  
  Note note;
  bool result = *(root) >> note;

  if (!result) {
    spdlog::error("Error parsing note.\n");
    return 4;
  }
  
  std::cout << "To: " << note.to() << "\n"
	    << "From: " << note.from() << "\n"
	    << "Heading: " << note.heading().value_or("<not set>") << "\n";

  for (const auto& body : note.body()) {
    std::cout << "BEGIN BODY:\n" << body << "\nEND BODY\n\n";
  }
  
  return 0;
}
