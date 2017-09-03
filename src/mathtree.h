#pragma once

#include <libcellml>

class MathTree
{
public:
    MathTree();
    ~MathTree();

    /**
     * @brief Add the math from the given component to this math tree.
     *
     * Parse the math from the given @c component and add it to this math tree.
     *
     * @param component The CellML component from whence to grab some math.
     *
     * @return @c true if math successfully added, @c false otherwise.
     */
    bool addComponentMathML(libcellml::ComponentPtr component);
};
