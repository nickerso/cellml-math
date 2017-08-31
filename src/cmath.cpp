#include <iostream>
#include <string>

#include <libcellml>

#include "modelloader.h"
#include "modelresolver.h"
#include "mathextractor.h"

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

    // load the model
    ModelLoader loader;
    if (! loader.loadModel(argv[1], ""))
    {
        std::cerr << "Error loading the model: " << argv[1] << std::endl;
        return -2;
    }
    libcellml::ModelPtr model = loader.getModel();
    std::string modelUrl = loader.getModelUrl();

    // resolve the model
    ModelResolver resolver;
    if (! resolver.resolveModel(model, modelUrl))
    {
        std::cerr << "Error resolving imports in the model: "
                  << argv[1] << std::endl;
        return -3;
    }

    // extract the math from the model
    MathExtractor extractor;
    if (! extractor.extractMath(model))
    {
        std::cerr << "Error extracting math from the model: " << argv[1] << std::endl;
        return -4;
    }
    return 0;
}
