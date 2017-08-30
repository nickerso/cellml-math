#include <iostream>
#include <string>

#include <libcellml>

#include "xmlutils.h"

static void usage(const char* progname)
{
    std::cerr << "CellML Math\n(using libCellML " << libcellml::versionString()
              << ")" << std::endl;
    std::cerr << "Usage: " << progname << " <CellML model location>" << std::endl;
    return;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        usage(argv[0]);
        return -1;
    }

    std::string modelUrl = XmlDoc::buildAbsoluteUri(argv[1], "");
    XmlDoc modelDoc;
    if (modelDoc.parseDocument(modelUrl) == 0)
    {
        std::string modelString = modelDoc.dumpString();
        // Parse
        libcellml::Parser parser(libcellml::Format::XML);
        libcellml::ModelPtr model = parser.parseModel(modelString);
        if (0 != parser.errorCount())
        {
            std::cerr << "Error parsing the CellML model: " << modelUrl << std::endl;
            for (size_t i = 0; i < parser.errorCount(); ++i) {
                std::cerr << parser.getError(i)->getDescription() << std::endl;
            }
            return -3;
        }
        libcellml::Validator validator;
        validator.validateModel(model);
        if (0 != validator.errorCount())
        {
            std::cerr << "Error validating the CellML model: " << modelUrl << std::endl;
            for (size_t i = 0; i < validator.errorCount(); ++i) {
                std::cerr << validator.getError(i)->getDescription() << std::endl;
            }
            return -4;
        }
    }
    else
    {
        std::cerr << "Error loading the model: " << modelUrl << std::endl;
        return -2;
    }
    return 0;
}
