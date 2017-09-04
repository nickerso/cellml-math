#include <iostream>
#include <string>

#include "mathtree.h"
#include "xmlutils.h"

#include "mathelement.h"

// forward declarations
static MathElement* createMathElement(MathElement* parent, xmlNodePtr node,
                                      libcellml::ComponentPtr component);

static std::string trim(const std::string& str,
                        const std::string& whitespace = " \t\n\r")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}

MathElement::MathElement(MathElement *parent) : parent(parent)
{

}

MathElement::MathElement()
{
    parent = nullptr;
}

MathElement::~MathElement()
{
    for (auto& child: children)
    {
        delete child;
    }
}

void NaryOperator::build(MathElement* parent, xmlNodePtr node,
                         libcellml::ComponentPtr component)
{
    // n-ary operator
    while (node)
    {
        children.push_back(createMathElement(parent, node, component));
        node = node->next;
    }
}

void Ci::build(MathElement* parent, xmlNodePtr node,
               libcellml::ComponentPtr component)
{
    xmlChar* text = xmlNodeListGetString(node->doc, node->children, 1);
    std::string textString(reinterpret_cast<const char *>(text));
    xmlFree(text);
    std::string variableName = trim(textString);
    std::cout << "<ci> variable name = " << variableName << std::endl;
    variable = component->getVariable(variableName);
}

static MathElement* createMathElement(MathElement* parent, xmlNodePtr node,
                                      libcellml::ComponentPtr component)
{
    std::string name(reinterpret_cast<const char *>(node->name));
    if (name == "apply")
    {
        std::string opName(reinterpret_cast<const char *>(node->children->name));
        if (opName == "eq")
        {
            Eq* eq = new Eq(parent);
            eq->build(eq, node->children->next, component);
            return eq;
        }
        else if (opName == "plus")
        {
            std::cout << "Have a plus!!\n";
        }
        else if (opName == "divide")
        {
            std::cout << "Have a divide!!!!\n";
        }
        std::cerr << "Don't know how to handle <apply> with the the MathML element: "
                  << opName << std::endl;
        return new MathElement(nullptr);
    }
    else if (name == "ci")
    {
        Ci* ci = new Ci(parent);
        ci->build(parent, node, component);
        return ci;
    }
    std::cout << "Don't know how to handle the MathML element: " << name << std::endl;
    return new MathElement(nullptr);
}

class MathTreeImpl {
public:
    MathTreeImpl()
    {
        root = new MathElement(nullptr);
    }
    ~MathTreeImpl()
    {
        delete root;
    }
    void appendChild(xmlNodePtr node, libcellml::ComponentPtr component)
    {
        root->children.push_back(createMathElement(nullptr, node, component));
    }

private:
    MathElement* root;
};

MathTree::MathTree()
{
    pImpl = new MathTreeImpl();
}

MathTree::~MathTree()
{
    delete pImpl;
}

bool MathTree::addComponentMathML(libcellml::ComponentPtr component)
{
    std::string componentMath = component->getMath();
    if (componentMath == "")
    {
        // no math to add
        return true;
    }
    XmlDoc doc;
    if (0 != doc.parseDocumentString(componentMath))
    {
        std::cerr << "Something went wrong parsing math for component: "
                  << component->getName() << std::endl;
        return false;
    }
    xmlDocPtr xml = doc.getXmlDoc();
    xmlNodePtr rootNode = xmlDocGetRootElement(xml);
    // if we have a math container so grab all child equations
    if (!xmlStrcmp(rootNode->name, BAD_CAST "math"))
    {
        xmlNodePtr child = rootNode->children;
        while (child)
        {
            pImpl->appendChild(child, component);
            child = child->next;
        }
    }
    else
    {
        // just a single equation to add
        pImpl->appendChild(rootNode, component);
    }
    return true;
}
