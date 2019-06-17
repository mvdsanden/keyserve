// m_cfgen.m.cpp                                              -*-c++-*-
#include <m_cfgen_commandlineargs.h>

#include <kdadm_document.h>
#include <kdadp_xmldocumentparser.h>

#include <iostream>
#include <memory>
#include <fstream>

using namespace MvdS;
using namespace MvdS::m_cfgen;

namespace {

  template <class T, class U>
  std::shared_ptr<U> openStream(const std::string& name, U *def)
  {
    if ("-" == name) {
      return std::shared_ptr<U>(def, [](U *obj) {});
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

  kdadm::Document document;

  {
    kdadp::XmlDocumentParser parser;

    auto inputStream = openStream<std::ifstream>(arguments.input(), &std::cin);
    if (!inputStream || !*inputStream.get()) {
      return 2;
    }

    if (!parser.parse(&document, *inputStream.get())) {
      return 4;
    }
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
