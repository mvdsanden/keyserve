// m_cfgen.m.cpp                                              -*-c++-*-
#include <kdadm_document.h>
#include <kdadp_xmldocumentparser.h>

#include <iostream>
#include <memory>
#include <fstream>

using namespace MvdS;
//using namespace MvdS::m_cfgen;

namespace {

  template <class T>
  std::shared_ptr<T> openStream(const std::string& name)
  {
    if ("-" == name) {
      return std::shared_ptr<T>(&std::cin, [](std::istream *obj) {});
    }

    return std::make_shared<T>(name);
  }

}; // anonymouse namespace

int main(int argc, char *argv[])
{
  // CmdlineArguments args;
  // if (!CmdlineArgumentsUtils::parse(&args, argc, argv)) {
  //   CmdlineArgumentsUtils::printUsage(argc, argv);
  //   return 1;
  // }

  kdadm::Document document;

  {
    kdadp::XmlDocumentParser parser;

    // auto inputStream = openStream<std::ifstream>(args.input());
    // if (!inputStream || !*inputStream.get()) {
    //   return 2;
    // }

    // if (!parser.parse(&document, inputStream.get())) {
    //   return 4;
    // }
  }

  {
    //    CodeGenerator codeGenerator(args, document);

    // auto outputStream = openStream<std::ofstream>(args.output());
    // if (!outputStream || !*outputStream.get()) {
    //   return 3;
    // }

    // if (!codeGenerator.generate(outputStream.get())) {
    //   return 5;
    // }
  }
  
  return 0;
}
