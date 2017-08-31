#include <iostream>
#include <string>

#include "modelresolver.h"
#include "modelloader.h"

class ModelResolverImp
{
public:
    ModelResolverImp()
    {
    }

    bool resolveComponent(libcellml::ComponentPtr component,
                          const std::string& baseUrl)
    {
        bool success = true;
        if (component->isImport())
        {
            libcellml::ImportPtr imp = component->getImport();
            if (! imp->isResolved())
            {
                ModelLoader loader;
                if (loader.loadModel(imp->getSource(), baseUrl))
                {
                    libcellml::ModelPtr model = loader.getModel();
                    std::string modelUrl = loader.getModelUrl();
                    imp->resolveImport(model);
                    resolveModel(model, modelUrl);
                }
                else
                {
                    success = false;
                }
            }
        }
        return success;
    }

    bool resolveComponents(libcellml::ComponentPtr component,
                           const std::string& baseUrl)
    {
        bool success = true;
        success = resolveComponent(component, baseUrl);
        for (size_t n = 0; n < component->componentCount();  ++n)
        {
            libcellml::ComponentPtr c = component->getComponent(n);
            if (! resolveComponents(c, baseUrl))
            {
                std::cerr << "Error resolving components: " << c->getName()
                          << "; in model: " << baseUrl
                          << std::endl;
                success = false;
            }
        }
        return success;
    }

    bool resolveModel(libcellml::ModelPtr model, const std::string& baseUrl)
    {
        bool success = true;
        for (size_t n = 0; n < model->componentCount();  ++n)
        {
            libcellml::ComponentPtr c = model->getComponent(n);
            if (! resolveComponents(c, baseUrl))
            {
                std::cerr << "Error resolving components: " << c->getName()
                          << "; in model: " << baseUrl
                          << std::endl;
                success = false;
            }
        }
        return success;
    }
};

ModelResolver::ModelResolver()
{
    pImpl = new ModelResolverImp();
}

ModelResolver::~ModelResolver()
{
    delete pImpl;
}

bool ModelResolver::resolveModel(libcellml::ModelPtr model,
                                 const std::string& modelUrl)
{
    return pImpl->resolveModel(model, modelUrl);
}

