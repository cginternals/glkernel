#include <iostream>
#include <string>

#include "scripting.h"

#include <cppassist/cmdline/ArgumentParser.h>

int main(int argc, char* argv[])
{
  cppassist::ArgumentParser argParser;
  argParser.parse(argc, argv);

  auto inFileName = argParser.value("--input");
  auto outFileName = argParser.value("--output");

  auto outFileType = outFileName.substr(outFileName.find_last_of('.') + 1);

  auto fromGeneratedKernel = argParser.isSet("-k");

  if (fromGeneratedKernel)
  {
    std::cout << "Converting kernel \"" << inFileName << "\" to output file \"" << outFileName << "\" (type: " << outFileType << ")" <<std::endl;
  }
  else
  {
    std::cout << "Using kernel description \"" << inFileName << "\" to generate kernel \"" << outFileName << "\" (type: " << outFileType << ")" << std::endl;
  }

  doScripting();
}
