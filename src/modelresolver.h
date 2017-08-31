#pragma once

#include <libcellml>

class ModelResolverImp;

class ModelResolver
{
public:
    ModelResolver();
    ~ModelResolver();

    bool resolveModel(libcellml::ModelPtr model,
                      const std::string& modelUrl);

private:
    ModelResolverImp* pImpl;
};

