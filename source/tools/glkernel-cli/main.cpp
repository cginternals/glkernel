#include <iostream>
#include <string>
#include <fstream>

#include <cppassist/logging/logging.h>

#include <glkernel/glkernel-version.h>

#include <cppassist/cmdline/ArgumentParser.h>
#include <cppassist/cmdline/CommandLineProgram.h>
#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineOption.h>
#include <cppassist/cmdline/CommandLineParameter.h>
#include <cppassist/cmdline/CommandLineSwitch.h>

#include "KernelGenerator.h"
#include "AbstractKernelExporter.h"

#include "JsonImporter.h"
#include "JsonExporter.h"
#include "PngExporter.h"


std::string extractInputFormat(const std::string & inFileName) {
    if (inFileName.find('.') == std::string::npos)
    {
        return "";
    }
    const auto inFileFormat = inFileName.substr(inFileName.find_last_of('.') + 1);
    if (inFileFormat != "js" && inFileFormat != "json")
    {
        return "";
    }
    return inFileFormat;
}

std::string extractOutputFormat(const std::string & outFileName, const bool shouldConvert) {
    if (outFileName.find('.') == std::string::npos)
    {
        if (shouldConvert)
        {
            return "png";
        }
        else
        {
            return "json";
        }
    }
    else
    {
        return outFileName.substr(outFileName.find_last_of('.') + 1);
    }
}

std::string extractOutputFile(const std::string & inputFile, const std::string & outputFileFormat) {
    const auto &inputFileName = inputFile.substr(0, inputFile.find_last_of('.'));
    return inputFileName + "." + outputFileFormat;
}

int main(int argc, char* argv[])
{
    auto program = cppassist::CommandLineProgram{
        "glkernel-cli",
        "glkernel-cli " GLKERNEL_VERSION,
        "A command line interface for generating and converting kernels."
    };

    auto actionRun = cppassist::CommandLineAction{
        "run",
        "Generate a kernel from a kernel description (.js file), or convert an existing kernel (.json file) into another representation"
    };

    auto paramInputFile = cppassist::CommandLineParameter{
        "inputFileName",
        cppassist::CommandLineParameter::NonOptional
    };

    auto optOutputFile = cppassist::CommandLineOption{
        "--output",
        "-o",
        "outputFileName",
        "File that the generated / converted kernel will be written to (defaults: <inputFileName>.json for generation, <inputFileName>.png for conversion)",
        cppassist::CommandLineOption::Optional
    };

    auto optOutputFormat = cppassist::CommandLineOption{
        "--format",
        "-f",
        "outputFileFormat",
        "File format for the generated / converted kernel (e.g., json, png, h)",
        cppassist::CommandLineOption::Optional
    };

    auto swForce = cppassist::CommandLineSwitch{
        "--force",
        "", // no short name, force should be explicit to avoid accidental overrides
        "Override the output file, if it exists",
        cppassist::CommandLineSwitch::Optional
    };

    auto swBeautify = cppassist::CommandLineSwitch{
        "--beautify",
        "-b",
        "Beautify the output (only applies to json output format)",
        cppassist::CommandLineSwitch::Optional
    };

    actionRun.add(&paramInputFile);
    actionRun.add(&optOutputFile);
    actionRun.add(&optOutputFormat);
    actionRun.add(&swForce);
    actionRun.add(&swBeautify);

    program.add(&actionRun);

    program.parse(argc, argv);

    if (program.selectedAction() && !program.hasErrors())
    {
        // TODO replace "if (! precondition) return" pattern with assertions
        const auto & inputFile = paramInputFile.value();
        const auto & inputFormat = extractInputFormat(inputFile);
        if (inputFormat.empty())
        {
            cppassist::error() << "Input file must have .js or .json file format";
            return 1;
        }
        const auto shouldConvert = inputFormat == "json";

        auto outputFormat = optOutputFormat.value();
        auto outputFile = optOutputFile.value();

        if (outputFormat.empty())
        {
            outputFormat = extractOutputFormat(outputFile, shouldConvert);
        }

        if (outputFile.empty())
        {
            outputFile = extractOutputFile(inputFile, outputFormat);
        }

        const auto shouldOverride = swForce.activated();
        auto outputExistsStream = std::ifstream{outputFile};
        if (outputExistsStream)
        {
            if (!shouldOverride)
            {
                cppassist::error() << "Output file \"" << outputFile << "\" exists! Use --force to override.";
                return 1;
            }
        }

        if (shouldConvert)
        {
            // Convert kernel to other representation
            cppassist::info() << "Converting kernel \"" << inputFile << "\" to output file \"" << outputFile
                              << "\" (format: " << outputFormat << ")";
            auto importer = KernelJsonImporter{inputFile};
            auto kernelVariant = importer.getKernel();

            // TODO: add support for png
            auto kernelExporter = KernelJsonExporter{kernelVariant, outputFile, swBeautify.activated()};
            kernelExporter.exportKernel();
        }
        else
        {
            // Generate kernel from description
            cppassist::info() << "Using kernel description \"" << inputFile << "\" to generate kernel \""
                              << outputFile << "\" (format: " << outputFormat << ")";

            auto kernelGenerator = KernelGenerator{inputFile};
            auto kernelVariant = kernelGenerator.generateKernelFromJavascript();

            if (outputFormat == "png")
            {
                auto kernelExporter = PngExporter{kernelVariant, outputFile};
                kernelExporter.exportKernel();
            }
            else if (outputFormat == "json")
            {
                auto kernelExporter = JsonExporter{kernelVariant, outputFile, swBeautify.activated()};
                kernelExporter.exportKernel();
            }
            else
            {
                cppassist::error() << "Invalid output format '" << outputFormat
                                   << "'. Output format must be png or json.";
                return 1;
            }
        }

        return 0;
        // Success
    }

    else
    {
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
