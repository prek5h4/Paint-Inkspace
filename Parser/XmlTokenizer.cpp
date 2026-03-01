#include "XmlTokenizer.h"
#include <cctype>

void XmlTokenizer::skipWhitespace(const std::string& xml, size_t& i) {
    while (i < xml.size() && isspace(xml[i])) {
        i++;
    }
}

bool XmlTokenizer::startsWithTag(const std::string& xml, size_t i) {
    skipWhitespace(xml, i);
    return i < xml.size() && xml[i] == '<';
}

XMLToken XmlTokenizer::readOpenTag(const std::string& xml, size_t& i) {
    skipWhitespace(xml, i);
    XMLToken token;
    token.type = XMLToken::Type::OpenTag;
    i++; // skip '<'
    
    size_t start = i;
    while(i < xml.size() && !isspace(xml[i]) && xml[i] != '>' && xml[i] != '/'){
        i++;
    }
    token.name = xml.substr(start, i - start);
    return token;
} 

XMLToken XmlTokenizer::readCloseTag(const std::string& xml, size_t& i) {
    skipWhitespace(xml, i);
    XMLToken token;
    token.type = XMLToken::Type::CloseTag;
    i++; // skip '<'
    
    if(i < xml.size() && xml[i] == '/'){
        i++; // skip '/'
    }
    
    size_t start = i;
    while(i < xml.size() && !isspace(xml[i]) && xml[i] != '>'){
        i++;
    }
    token.name = xml.substr(start, i - start);
    
    // Skip to '>'
    while(i < xml.size() && xml[i] != '>'){
        i++;
    }
    if(i < xml.size()){
        i++; // skip '>'
    }
    
    return token;
} 

std::vector<XMLToken> XmlTokenizer::readAttributes(const std::string& xml, size_t& i){
    std::vector<XMLToken> attributes;
    skipWhitespace(xml, i);
    
    while (i < xml.size() && xml[i] != '>' && xml[i] != '/') {
        XMLToken attrToken;
        attrToken.type = XMLToken::Type::Attribute;

        size_t start = i;
        while (i < xml.size() && xml[i] != '=' && !isspace(xml[i])) {
            i++;
        }
        attrToken.name = xml.substr(start, i - start);

        skipWhitespace(xml, i);
        if (i < xml.size() && xml[i] == '=') {
            i++;
            skipWhitespace(xml, i);
            if (i < xml.size() && (xml[i] == '"' || xml[i] == '\'')) {
                char quote = xml[i];
                i++;
                start = i;
                while (i < xml.size() && xml[i] != quote) {
                    i++;
                }
                attrToken.value = xml.substr(start, i - start);
                i++; // skip closing quote
            }
        }
        attributes.push_back(attrToken);
        skipWhitespace(xml, i);
    }
    return attributes;
}

XMLToken XmlTokenizer::readTextNode(const std::string& xml, size_t& i){
    skipWhitespace(xml, i);
    XMLToken token;
    token.type = XMLToken::Type::TextNode;
    size_t start = i;
    while (i < xml.size() && xml[i] != '<') {
        i++;
    }
    token.value = xml.substr(start, i - start);
    return token;
}

