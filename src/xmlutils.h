#pragma once

#include <libxml/tree.h>

class XmlDoc
{
public:
    XmlDoc();
    ~XmlDoc();
    static std::string buildAbsoluteUri(const std::string& uri,
                                        const std::string& base);
    int parseDocument(const std::string& url);
    // this one removes blank nodes and hides errors/warnings
    int parseDocumentString(const std::string& docString);
    std::string dumpString() const;

    xmlDocPtr getXmlDoc();

private:
    void* mXmlDocPtr;
};
