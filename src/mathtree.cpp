#include <iostream>
#include <string>

#include "mathtree.h"
#include "xmlutils.h"

MathTree::MathTree()
{

}

MathTree::~MathTree()
{

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
    std::string s = doc.dumpString();
    std::cout << "**********"
              << s
              << "**********" << std::endl;
    return true;
}
