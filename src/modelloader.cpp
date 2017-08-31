#include <iostream>
#include <string>

#include "modelloader.h"
#include "xmlutils.h"

class ModelLoaderImp
{
public:
    ModelLoaderImp() : model(nullptr), url("")
    {
    }

    libcellml::ModelPtr model;
    std::string url;
};

ModelLoader::ModelLoader()
{
    pImpl = new ModelLoaderImp();
}

ModelLoader::~ModelLoader()
{
    delete pImpl;
}

bool ModelLoader::loadModel(const std::string& modelUrl,
                            const std::string& baseUrl)
{
    std::string url = XmlDoc::buildAbsoluteUri(modelUrl, baseUrl);
    XmlDoc modelDoc;
    if (modelDoc.parseDocument(url) == 0)
    {
        std::string modelString = modelDoc.dumpString();
        // Parse
        libcellml::Parser parser(libcellml::Format::XML);
        libcellml::ModelPtr model = parser.parseModel(modelString);
        if (0 != parser.errorCount())
        {
            std::cerr << "Error parsing the CellML model: " << url
                      << std::endl;
            for (size_t i = 0; i < parser.errorCount(); ++i) {
                std::cerr << parser.getError(i)->getDescription() << std::endl;
            }
            return false;
        }
        libcellml::Validator validator;
        validator.validateModel(model);
        if (0 != validator.errorCount())
        {
            std::cerr << "Error validating the CellML model: " << url
                      << std::endl;
            for (size_t i = 0; i < validator.errorCount(); ++i) {
                std::cerr << validator.getError(i)->getDescription()
                          << std::endl;
            }
            return false;
        }
        pImpl->model = model;
        pImpl->url = url;
    }
    return true;
}

libcellml::ModelPtr ModelLoader::getModel() const
{
    return pImpl->model;
}

std::string ModelLoader::getModelUrl() const
{
    return pImpl->url;
}
