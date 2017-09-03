#include <iostream>
#include <string>

#include "mathextractor.h"
#include "mathtree.h"

class MathExtractorImpl
{
public:
    MathExtractorImpl()
    {
        tree = new MathTree();
    }
    ~MathExtractorImpl()
    {
        delete tree;
    }

    bool extractMathFromComponent(libcellml::ComponentPtr component)
    {
        bool success = true && tree->addComponentMathML(component);
        for (size_t n=0; n<component->componentCount(); ++n)
        {
            libcellml::ComponentPtr c = component->getComponent(n);
            success = success && extractMathFromComponent(c);
        }
        return success;
    }

private:
    MathTree* tree;
};

MathExtractor::MathExtractor()
{
    pImpl = new MathExtractorImpl();
}

MathExtractor::~MathExtractor()
{
    delete pImpl;
}

bool MathExtractor::extractMath(libcellml::ModelPtr model)
{
    bool success = true;
    for (size_t n = 0; n < model->componentCount();  ++n)
    {
        libcellml::ComponentPtr c = model->getComponent(n);
        if (! pImpl->extractMathFromComponent(c))
        {
            std::cerr << "Error extracting math from component (or children): " << c->getName()
                      << "; in model: " << model->getName()
                      << std::endl;
            success = false;
        }
    }
    return success;
}
