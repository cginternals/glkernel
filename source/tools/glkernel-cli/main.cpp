#include <iostream>
#include <string>

#include <cppassist/logging/logging.h>

#include <glkernel/glkernel-version.h>

#include <cppassist/cmdline/ArgumentParser.h>
#include <cppassist/cmdline/CommandLineProgram.h>
#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineOption.h>
#include <cppassist/cmdline/CommandLineSwitch.h>


int main(int argc, char* argv[])
{
    auto program = cppassist::CommandLineProgram{
        "glkernel-cli",
        "glkernel-cli " GLKERNEL_VERSION,
        "A command line interface for generating and converting kernels."};


    auto actionRun = cppassist::CommandLineAction{"run",
        "Generate a kernel from a kernel description or convert an existing kernel into another representation"};

    auto optInputFile = cppassist::CommandLineOption{
        "--input",
        "-i",
        "inFileName",
        "Kernel description or generated kernel",
        cppassist::CommandLineOption::NonOptional};

    auto optOutputFile = cppassist::CommandLineOption{
        "--output",
        "-o",
        "outFileName",
        "File that the generated / converted kernel will be written to",
        cppassist::CommandLineOption::NonOptional};

    auto optOutputFormat = cppassist::CommandLineOption{
        "--format",
        "-f",
        "outFileFormat",
        "File format for the generated / converted kernel (e.g. json, png)",
        cppassist::CommandLineOption::Optional};

    auto swConvert = cppassist::CommandLineSwitch{
        "--convert",
        "-c",
        "Convert an existing kernel into another representation instead of generating a new one",
        cppassist::CommandLineSwitch::Optional};


    actionRun.add(&optInputFile);
    actionRun.add(&optOutputFile);
    actionRun.add(&optOutputFormat);
    actionRun.add(&swConvert);

    program.add(&actionRun);

    program.parse(argc, argv);

    if (program.selectedAction() && !program.hasErrors()) {

        // Generate kernel from description
        const auto &inFileName = optInputFile.value();
        const auto &outFileName = optOutputFile.value();
        auto outFileFormat = optOutputFormat.value();
        if (outFileFormat.empty()) {
            if (outFileName.find('.') == std::string::npos) {
                outFileFormat = "json";
            } else {
                outFileFormat = outFileName.substr(outFileName.find_last_of('.') + 1);
            }
        }

        if (swConvert.activated()) {
            // Convert kernel to other representation
            cppassist::info() << "Converting kernel \"" << inFileName << "\" to output file \"" << outFileName
                              << "\" (format: " << outFileFormat << ")";
        } else {
            // Generate kernel from description
            cppassist::info() << "Using kernel description \"" << inFileName << "\" to generate kernel \""
                              << outFileName << "\" (format: " << outFileFormat << ")";
        }

        return 0;
        // Success
    }

    else {
        // Print help
        program.print(program.help(program.selectedAction()));

        // Print errors
        if (program.hasErrors() && program.selectedAction())
        {
            std::string error = program.selectedAction()->errors()[0];
            program.print("Error: " + error);

            return 1;
        }
    }

    return 0;
}