#include "KernelJsonExporter.hpp"

#include <iostream>
#include <fstream>

void KernelJsonExporter::export() {
    const auto jsonArray = toJsonArray(m_kernel);

    writeToFile(jsonArray);
}

cppexpose::Variant KernelJsonExporter::toJsonArray(const cppexpose::Variant & kernel) {

    /* TODO convert kernel to json-stringifyable variant array
     * check kernel.hasType<glkernel::kernel(4|3|2|1)>, and build corresponding appendComponentToVariantArray lambda
     */

    return cppexpose::Variant::fromValue(glkernel::kernel4{ });
}


void KernelJsonExporter::writeToFile(const cppexpose::Variant & jsonArray) {
    // TODO: check if file exists
    // if (!force && fileExists(outFileName)) { std::cerr << "... / throw?
    std::ofstream outStream(m_outFileName);

    if (!outStream.is_open())
    {
        // TODO exception instead?
        std::cerr << "ERROR: Output file could not be created. Aborting..." << std::endl;
    }

    outStream << stringify(jsonArray) << std::endl;
}

std::string KernelJsonExporter::stringify(const cppexpose::Variant &array) {
    return cppexpose::JSON::stringify(array, cppexpose::JSON::OutputMode::Beautify);
}
