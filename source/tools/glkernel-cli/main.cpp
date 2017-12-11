#include <iostream>
#include <string>

#include <cppassist/logging/logging.h>

#include <glkernel/glkernel-version.h>

#include <cppassist/cmdline/ArgumentParser.h>
#include <cppassist/cmdline/CommandLineProgram.h>
#include <cppassist/cmdline/CommandLineAction.h>
#include <cppassist/cmdline/CommandLineOption.h>
#include <cppassist/cmdline/CommandLineParameter.h>


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
        "File format for the generated / converted kernel (e.g. .json, .png, .h)",
        cppassist::CommandLineOption::Optional
    };

    actionRun.add(&paramInputFile);
    actionRun.add(&optOutputFile);
    actionRun.add(&optOutputFormat);

    program.add(&actionRun);

    program.parse(argc, argv);

    if (program.selectedAction() && !program.hasErrors())
    {
        const auto &inFileName = paramInputFile.value();

        if (inFileName.find('.') == std::string::npos)
        {
            cppassist::error() << "Input file must have .js or .json file format";
            return 1;
        }
        const auto inFileFormat = inFileName.substr(inFileName.find_last_of('.') + 1);
        if (inFileFormat != "js" && inFileFormat != "json")
        {
            cppassist::error() << "Input file must have .js or .json file format";
            return 1;
        }
        const auto shouldConvert = inFileFormat == "json";

        auto outFileFormat = optOutputFormat.value();
        auto outFileName = optOutputFile.value();

        if (outFileFormat.empty())
        {
            if (outFileName.find('.') == std::string::npos)
            {
                if (shouldConvert)
                {
                    outFileFormat = "png";
                }
                else
                {
                    outFileFormat = "json";
                }
            }
            else
            {
                outFileFormat = outFileName.substr(outFileName.find_last_of('.') + 1);
            }
        }

        if (outFileName.empty())
        {
            outFileName = inFileName.substr(0, inFileName.find_last_of('.')) + "." + outFileFormat;
        }

        if (shouldConvert)
        {
            // Convert kernel to other representation
            cppassist::info() << "Converting kernel \"" << inFileName << "\" to output file \"" << outFileName
                              << "\" (format: " << outFileFormat << ")";
        }
        else
        {
            // Generate kernel from description
            cppassist::info() << "Using kernel description \"" << inFileName << "\" to generate kernel \""
                              << outFileName << "\" (format: " << outFileFormat << ")";
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