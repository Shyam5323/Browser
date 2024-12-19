#ifndef STARTTOKEN_H
#define STARTTOKEN_H

#include <string>
#include <map>
#include <iostream>

#include <HTMLtokens.hpp>

class StartToken : public HTMLToken
{
public:
    StartToken();
    StartToken(char tokenName);
    bool isSelfClosing() const;
    void setSelfClosing(bool closing);
    std::map<std::string, std::string> getAttributes() const;
    void addToCurrentAttributeName(char next_char);
    void addToCurrentAttributeValue(char next_char);
    std::string getAttributeValue(std::string attribute_name) const;
    bool containsAttribute(std::string attribute_name) const;
    void processCurrentAttribute();
    bool isStartToken() const;

private:
    bool selfClosing;
    std::map<std::string, std::string> attributes;
    std::string currentAttributeName;
    std::string currentAttributeValue;
};

#endif
