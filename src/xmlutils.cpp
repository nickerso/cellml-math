/**
  * Extracted from CSim...
  */

#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/uri.h>

// FIXME: need to do this better?
#ifdef _MSC_VER
#  include <direct.h>
#  define PATH_MAX_SIZE 4096
#  define getcwd _getcwd
#else
#  include <unistd.h>
#  define PATH_MAX_SIZE pathconf(".",_PC_PATH_MAX)
#endif

#include <curl/curl.h>

#include "xmlutils.h"

class LibXMLWrapper
{
public:
    LibXMLWrapper()
    {
        std::cout << "initialise curl\n";
        curl_global_init(CURL_GLOBAL_DEFAULT);
        std::cout << "initialise libxml\n";
        /* Init libxml */
        xmlInitParser();
        LIBXML_TEST_VERSION
    }
    ~LibXMLWrapper()
    {
        std::cout << "terminate libxml\n";
        /* Shutdown libxml */
        xmlCleanupParser();
        std::cout << "cleanup curl\n";
        curl_global_cleanup();
    }
};

static LibXMLWrapper dummyWrapper;

XmlDoc::XmlDoc() : mXmlDocPtr(0)
{
}

XmlDoc::~XmlDoc()
{
    if (mXmlDocPtr)
    {
        xmlFreeDoc(static_cast<xmlDocPtr>(mXmlDocPtr));
    }
}

// See http://www.cplusplus.com/forum/unices/45878/
// callback function writes data to a std::ostream
static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
    if (userp)
    {
        std::ostream& os = *static_cast<std::ostream*>(userp);
        std::streamsize len = size * nmemb;
        if(os.write(static_cast<char*>(buf), len))
            return len;
    }
    return 0;
}

/**
 * timeout is in seconds
 **/
CURLcode curl_read(const std::string& url, std::ostream& os, long timeout = 30)
{
    CURLcode code(CURLE_FAILED_INIT);
    CURL* curl = curl_easy_init();
    if (curl)
    {
        if (CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
                                                 &data_write))
           && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS,
                                                   1L))
           && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION,
                                                   1L))
           && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEDATA,
                                                   &os))
           && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT,
                                                   timeout))
           && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL,
                                                   url.c_str())))
        {
            code = curl_easy_perform(curl);
        }
        curl_easy_cleanup(curl);
    }
    return code;
}

int XmlDoc::parseDocument(const std::string& url)
{
    // we use libCURL to grab files to avoid trouble with HTTP/HTTPS
    std::ostringstream oss;
    std::string content;
    if (CURLE_OK == curl_read(url, oss))
    {
        // Web page successfully written to string
        content = std::string(oss.str());
    }
    if (content.empty())
    {
        std::cerr << "Error parsing document from URL: **" << url << "**\n";
        return -1;
    }
    return parseDocumentString(content);
}

std::string XmlDoc::buildAbsoluteUri(const std::string& uri,
                                     const std::string& base)
{
    std::string b = base;
    if (b.empty())
    {
        int size = PATH_MAX_SIZE;
        char* cwd = (char*)malloc(size);
        if (!getcwd(cwd,size)) cwd[0] = '\0';
        b = "file://";
        b += cwd;
        b += "/";
        free(cwd);
    }
    xmlChar* fullURL = xmlBuildURI(BAD_CAST uri.c_str(), BAD_CAST b.c_str());
    std::string url((char*)fullURL);
    xmlFree(fullURL);
    return url;
}

int XmlDoc::parseDocumentString(const std::string& ds)
{
    xmlDocPtr doc = xmlParseDoc(BAD_CAST ds.c_str());
    if (doc == NULL)
    {
        std::cerr << "Error parsing document from string." << std::endl;
        return -1;
    }
    mXmlDocPtr = static_cast<void*>(doc);
    return 0;
}

std::string XmlDoc::dumpString() const
{
    xmlDocPtr doc = static_cast<xmlDocPtr>(mXmlDocPtr);
    if (doc == NULL)
    {
        std::cerr << "Error dumping string\n";
        return "";
    }
    xmlChar *s;
    int size;
    xmlDocDumpMemory(doc, &s, &size);
    if (s == NULL)
    {
        return "";
    }
    std::string out = std::string((char*)s);
    xmlFree(s);
    return out;
}
