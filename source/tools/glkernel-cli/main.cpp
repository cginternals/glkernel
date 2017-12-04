#include <iostream>
#include <string>

#include <cppassist/logging/logging.h>

#include <cppassist/cmdline/ArgumentParser.h>
#include <cppassist/cmdline/CommandLineProgram.h>
#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineCommand.h>
#include <cppassist/cmdline/CommandLineOption.h>
#include <cppassist/cmdline/CommandLineSwitch.h>
#include <cppassist/cmdline/CommandLineParameter.h>


int main(int argc, char* argv[])
{
    auto program = cppassist::CommandLineProgram{
        "glkernel-cli",
        "glkernel-cli", // TODO version, license?
        "A command line interface for generating and converting kernels."};


    auto actionGenerate = cppassist::CommandLineAction{"generate", "Generate a kernel from a kernel description"};
    auto actionConvert = cppassist::CommandLineAction{"convert", "Convert an existing kernel into another representation"};

    auto commandGenerate = cppassist::CommandLineCommand{"generate"};
    auto commandConvert = cppassist::CommandLineCommand{"convert"};

    auto optInputFile = cppassist::CommandLineOption{"--input", "-i", "inFileName",
        "Kernel description or generated kernel", cppassist::CommandLineOption::NonOptional};
    auto optOutputFile = cppassist::CommandLineOption{"--output", "-o", "outFileName",
        "File that the generated / converted kernel will be written to", cppassist::CommandLineOption::NonOptional};
    auto optOutputFormat = cppassist::CommandLineOption{"--format", "-f", "outFileFormat",
        "File format for the generated / converted kernel (e.g. json, png)", cppassist::CommandLineOption::Optional};

    actionGenerate.add(&commandGenerate);
    actionGenerate.add(&optInputFile);
    actionGenerate.add(&optOutputFile);
    actionGenerate.add(&optOutputFormat);

    actionConvert.add(&commandConvert);
    actionConvert.add(&optInputFile);
    actionConvert.add(&optOutputFile);
    actionConvert.add(&optOutputFormat);

    program.add(&actionGenerate);
    program.add(&actionConvert);

    program.parse(argc, argv);

    if (program.selectedAction() && !program.hasErrors()) {

        // Generate kernel from description
        if (program.selectedAction() == &actionGenerate) {
            const auto& inFileName = optInputFile.value();
            const auto& outFileName = optOutputFile.value();
            auto outFileFormat = optOutputFormat.value();
            if (outFileFormat.empty()) {
                if (outFileName.find('.') == std::string::npos) {
                    outFileFormat = "json";
                } else {
                    outFileFormat = outFileName.substr(outFileName.find_last_of('.') + 1);
                }
            }
            cppassist::info() << "Using kernel description \"" << inFileName << "\" to generate kernel \"" << outFileName << "\" (format: " << outFileFormat << ")";
        }

        // Convert kernel to other representation
        else if (program.selectedAction() == &actionConvert) {
            const auto& inFileName = optInputFile.value();
            const auto& outFileName = optOutputFile.value();
            auto outFileFormat = optOutputFormat.value();
            if (outFileFormat.empty()) {
                outFileFormat = outFileName.substr(outFileName.find_last_of('.') + 1);
                if (outFileName.find('.') == std::string::npos) {
                    outFileFormat = "json";
                } else {
                    outFileFormat = outFileName.substr(outFileName.find_last_of('.') + 1);
                }
            }
            cppassist::info() << "Converting kernel \"" << inFileName << "\" to output file \"" << outFileName << "\" (format: " << outFileFormat << ")";
        }

        // Success
        return 0;
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