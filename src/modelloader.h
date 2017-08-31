#pragma once

#include <libcellml>

class ModelLoaderImp;

class ModelLoader
{
public:
    ModelLoader();
    ~ModelLoader();

    /**
     * @brief Load the given model.
     *
     * Will attempt to parse, load, and validate the model at the specified
     * @c modelUrl. The @c baseUrl will be used to resolve relative
     * @c modelUrl's. Will only succeed if the model is successfully retrieved,
     * parsed, validated.
     *
     * @param modelUrl The URL of the model to load.
     * @param baseUrl The base URL to use to resolve relative model URL's.
     * @return @c true if the model is successfully retrieved, parsed, and
     * validated, @c false otherwise.
     */
    bool loadModel(const std::string& modelUrl, const std::string& baseUrl);

    /**
     * @brief Get the loaded model.
     *
     * @return The loaded model, if a model has been successfully loaded.
     * @c nullptr otherwise.
     */
    libcellml::ModelPtr getModel() const;

    /**
     * @brief Get the absolute URL that had been resolved for the loaded model.
     *
     * @return The resolved absolute URL for a successfully loaded model, the
     * empty string otherwise.
     */
    std::string getModelUrl() const;

private:
    ModelLoaderImp* pImpl;
};

