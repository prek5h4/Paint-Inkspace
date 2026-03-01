#pragma once
#include <string>
#include <vector>

struct XMLToken {
    enum class Type {
        OpenTag,
        CloseTag,
        Attribute,
        TextNode
    };

    Type type;
    std::string name; // for tags and attributes
    std::string value; // for attributes and text nodes
};

class XmlTokenizer {
public:
    XmlTokenizer() = default;
    ~XmlTokenizer() = default;

    std::vector<XMLToken> tokenizeXML(const std::string& xml);
    
private:
    static bool startsWithTag(const std::string& xml, size_t i);
    static XMLToken readOpenTag(const std::string& xml, size_t& i);
    static XMLToken readCloseTag(const std::string& xml, size_t& i);
    static std::vector<XMLToken> readAttributes(const std::string& xml, size_t& i);
    static XMLToken readTextNode(const std::string& xml, size_t& i);
    static void skipWhitespace(const std::string& xml, size_t& i);
};