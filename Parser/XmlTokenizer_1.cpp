#include "XmlTokenizer.h"

std::vector<XMLToken> XmlTokenizer::tokenizeXML(const std::string& xml) {
    std::vector<XMLToken> tokens;
    size_t i = 0;
    
    while (i < xml.size()) {
        skipWhitespace(xml, i);
        
        if (i >= xml.size()) break;
        
        if (xml[i] == '<') {
            // Skip XML declaration <?xml ... ?>
            if (i + 1 < xml.size() && xml[i + 1] == '?') {
                while (i < xml.size() && !(xml[i] == '?' && i + 1 < xml.size() && xml[i + 1] == '>')) {
                    i++;
                }
                i += 2; // skip ?>
                continue;
            }
            
            // Check if it's a close tag
            if (i + 1 < xml.size() && xml[i + 1] == '/') {
                tokens.push_back(readCloseTag(xml, i));
            } else {
                // Open tag
                XMLToken openTag = readOpenTag(xml, i);
                tokens.push_back(openTag);
                
                // Read attributes
                auto attrs = readAttributes(xml, i);
                tokens.insert(tokens.end(), attrs.begin(), attrs.end());
                
                // Check for self-closing tag
                skipWhitespace(xml, i);
                bool selfClosing = false;
                if (i < xml.size() && xml[i] == '/') {
                    selfClosing = true;
                    i++; // skip '/'
                }
                
                // Skip to '>'
                while (i < xml.size() && xml[i] != '>') {
                    i++;
                }
                if (i < xml.size()) {
                    i++; // skip '>'
                }
                
                // If self-closing, immediately add a close tag
                if (selfClosing) {
                    XMLToken closeTag;
                    closeTag.type = XMLToken::Type::CloseTag;
                    closeTag.name = openTag.name;
                    tokens.push_back(closeTag);
                }
            }
        } else {
            // Text node
            XMLToken textNode = readTextNode(xml, i);
            // Only add non-empty text nodes
            if (!textNode.value.empty()) {
                // Trim whitespace
                size_t start = 0;
                size_t end = textNode.value.length();
                while (start < end && isspace(textNode.value[start])) start++;
                while (end > start && isspace(textNode.value[end - 1])) end--;
                
                if (start < end) {
                    textNode.value = textNode.value.substr(start, end - start);
                    tokens.push_back(textNode);
                }
            }
        }
    }
    
    return tokens;
}