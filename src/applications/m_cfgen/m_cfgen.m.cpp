// m_cfgen.m.cpp                                              -*-c++-*-
#include <m_cfgen_commandlineargs.h>
#include <m_cfgen_validator.h>
#include <m_cfgen_codegeneratorfactory.h>
#include <m_cfgen_codegenerator.h>

#include <kdadm_document.h>
#include <kdadp_xmldocumentparser.h>

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <iostream>
#include <memory>
#include <fstream>

using namespace MvdS;
using namespace MvdS::m_cfgen;

namespace {

  struct Logger {

    std::shared_ptr<spdlog::logger> d_logger;
    
    Logger(const CommandlineArgs& arguments)      
    {

      d_logger = spdlog::basic_logger_mt<spdlog::async_factory>("logger", "cfgen.log");
      spdlog::set_default_logger(d_logger);
      spdlog::set_level(spdlog::level::debug);
    }

    ~Logger()
    {
    }

  };
  
  template <class T, class U>
  std::shared_ptr<U> openStream(const std::string& name, U *defaultStream)
  {
    if ("-" == name) {
      return std::shared_ptr<U>(defaultStream, [](U *obj) {});
    }

    return std::make_shared<T>(name);
  }

}; // anonymouse namespace

int main(int argc, char *argv[])
{
  CommandlineArgs arguments;
  CommandlineArgsUtil::parse(&arguments, {argv, argc});
 
  if (arguments.printUsage()) {
    CommandlineArgsUtil::printUsage(&std::cout, {argv, argc});
    return 1;
  }

  Logger logger(arguments);
  spdlog::info("Init: {}", argv[0]);
  
  kdadm::Document document;

  {
    kdadp::XmlDocumentParser parser;

    auto inputStream = openStream<std::ifstream>(arguments.input(), &std::cin);
    if (!inputStream || !*inputStream.get()) {
      std::cerr << "Error opening input stream.\n";
      return 2;
    }

    if (!parser.parse(&document, *inputStream.get(), arguments.input())) {
      return 3;
    }
  }

  {
    Validator validator(arguments);

    if (!validator.validate(&document)) {
      return 4;
    }
  }

  {
    CodeGeneratorFactory factory;
    std::unique_ptr<CodeGenerator> generator(factory.create(arguments));
    if (!generator) {
      return 6;
    }

    generator->generate(document);
  }
  
  return 0;
}
