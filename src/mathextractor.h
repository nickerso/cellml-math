#pragma once

#include <libcellml>

class MathExtractorImpl;

class MathExtractor
{
public:
    MathExtractor();
    ~MathExtractor();

    /**
     * @brief Extract all the math from the given model
     *
     * @param model The CellML model from which to extract the math.
     *
     * @return @c true if the math is successfully extracted, @c false otherwise.
     */
    bool extractMath(libcellml::ModelPtr model);

private:
    MathExtractorImpl* pImpl;
};
