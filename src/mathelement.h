#pragma once

#include <vector>
#include <libcellml>

enum MathType {
    MATH_UNDEFINED,
    MATH_EXPRESSION,
    MATH_EQ,
    MATH_CI
};

class MathElement {
public:
    MathElement(MathElement* parent);
    ~MathElement();

    inline virtual enum MathType getType() const
    {
        return MATH_UNDEFINED;
    }
    virtual void build(MathElement* parent, xmlNodePtr node,
                       libcellml::ComponentPtr component)
    {

    }

    MathElement* parent;
    std::vector<MathElement*> children;

private:
    MathElement();
};

class MathExpression : public MathElement
{
public:
    MathExpression() : MathElement(nullptr)
    {
    }

    inline virtual enum MathType getType() const
    {
        return MATH_EXPRESSION;
    }

    std::vector<libcellml::VariablePtr> variables;
};

class NaryOperator : public MathElement {
public:
    NaryOperator(MathElement* parent) : MathElement(parent)
    {
    }

    inline virtual enum MathType getType() const
    {
        return MATH_UNDEFINED;
    }

    virtual void build(MathElement* parent, xmlNodePtr node,
                       libcellml::ComponentPtr component);
};

class Eq : public NaryOperator {
public:
    Eq(MathElement* parent) : NaryOperator(parent)
    {
    }

    inline enum MathType getType() const
    {
        return MATH_EQ;
    }
};

class Ci : public MathElement {
public:
    Ci(MathElement* parent) : MathElement(parent)
    {
    }

    inline enum MathType getType() const
    {
        return MATH_CI;
    }
    void build(MathElement* parent, xmlNodePtr node,
               libcellml::ComponentPtr component);
    libcellml::VariablePtr variable;
};
