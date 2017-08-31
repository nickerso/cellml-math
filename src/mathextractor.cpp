#include <iostream>
#include <string>

#include "mathextractor.h"

class MathExtractorImpl
{
public:
    MathExtractorImpl()
    {

    }
    ~MathExtractorImpl()
    {

    }

};

MathExtractor::MathExtractor() : pImpl(nullptr)
{

}

MathExtractor::~MathExtractor()
{
    if (pImpl) delete pImpl;
}

bool MathExtractor::extractMath(libcellml::ModelPtr model)
{
    return true;
}
