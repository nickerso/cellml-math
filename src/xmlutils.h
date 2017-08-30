#pragma once

#include <vector>

class XmlDoc
{
public:
    XmlDoc();
    ~XmlDoc();
    static std::string buildAbsoluteUri(const std::string& uri,
                                        const std::string& base);
    int parseDocument(const std::string& url);
    int parseDocumentString(const std::string& docString);
    std::string dumpString() const;
private:
    void* mXmlDocPtr;
};
