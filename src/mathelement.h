#pragma once

#include <vector>
#include <libcellml>

enum MathType {
    MATH_UNDEFINED,
    MATH_EQ,
    MATH_CI
};

class MathElement {
public:
    MathElement();
    ~MathElement();
    std::vector<MathElement*> children;
    inline virtual enum MathType getType() const
    {
        return MATH_UNDEFINED;
    }
    virtual void build(xmlNodePtr node, libcellml::ComponentPtr component)
    {}
};

class NaryOperator : public MathElement {
public:
    inline virtual enum MathType getType() const
    {
        return MATH_UNDEFINED;
    }
    virtual void build(xmlNodePtr node, libcellml::ComponentPtr component);
};

class Eq : public NaryOperator {
public:
    inline enum MathType getType() const
    {
        return MATH_EQ;
    }
};

class Ci : public MathElement {
public:
    inline enum MathType getType() const
    {
        return MATH_CI;
    }
    void build(xmlNodePtr node, libcellml::ComponentPtr component);
    libcellml::VariablePtr variable;
};
