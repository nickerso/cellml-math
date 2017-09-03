#include <iostream>
#include <string>

#include "mathtree.h"
#include "xmlutils.h"

class MathElement {
public:
    MathElement()
    {
    }
    ~MathElement()
    {
        for (auto& child: children)
        {
            delete child;
        }
    }
    std::string name;
    std::vector<MathElement*> children;
};

static MathElement* createMathElement(xmlNodePtr node,
                                      libcellml::ComponentPtr component)
{
    std::string name(reinterpret_cast<const char *>(node->name));
    if (name == "apply")
    {
        std::cout << "Haven an apply\n";
        std::string opName(reinterpret_cast<const char *>(node->children->name));
        if (opName == "eq")
        {
            std::cout << "Have a EQ!!\n";
        }
        else if (opName == "plus")
        {
            std::cout << "Have a plus!!\n";
        }
        else if (opName == "divide")
        {
            std::cout << "Have a divide!!!!\n";
        }
    }
    return new MathElement();
}

class MathTreeImpl {
public:
    MathTreeImpl()
    {
        root = new MathElement();
    }
    ~MathTreeImpl()
    {
        delete root;
    }
    void appendChild(xmlNodePtr node, libcellml::ComponentPtr component)
    {
        root->children.push_back(createMathElement(node, component));
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
