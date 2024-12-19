#ifndef ENDTOKEN_H
#define ENDTOKEN_H

#include <string>
#include <map>
#include <HTMLtokens.hpp>
#include <iostream>

class EndToken : public HTMLToken
{
public:
    EndToken();
    EndToken(char token_name);
    bool isSelfClosing() const;
    void setSelfClosing(bool closing);
    std::map<std::string, std::string> getAttributes() const;
    void addToCurrentAttributeName(char next_char);
    void addToCurrentAttributeValue(char next_char);
    std::string getAttributeValue(std::string attribute_name) const;
    bool containsAttribute(std::string attribute_name) const;
    void processCurrentAttribute();
    bool isEndToken() const;

private:
    bool selfClosing;
};

#endif
