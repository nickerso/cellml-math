#include <iostream>
#include <string>

#include <libcellml>

#include "modelloader.h"

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

    ModelLoader loader;
    if (loader.loadModel(argv[1], ""))
    {
        libcellml::ModelPtr model = loader.getModel();
        std::string modelUrl = loader.getModelUrl();
    }
    else
    {
        std::cerr << "Error loading the model: " << argv[1] << std::endl;
        return -2;
    }
    return 0;
}
