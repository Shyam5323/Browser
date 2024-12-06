#ifndef DOCTYPETOKENS_H
#define DOCTYPETOKENS_H

#include <HTMLTokens.hpp>
#include <string>

class DOCTYPEToken : HTMLToken
{
    DOCTYPEToken();
    DOCTYPEToken(char token);
    bool isDoctypeToken() const;
    void setIsNameSet(bool isSet) {}
    bool isNameSet() const { return false; }
    bool isPublicIdentifierSet() const { return false; }
    bool isSystemIdentifierSet() const { return false; }
    std::string getPublicIdentifier() const { return NULL; }
    std::string getSystemIdentifier() const { return NULL; }

private:
    bool nameSet;
    bool publicIdentifierSet;
    bool systemIdentifierSet;
    std::string publicIdentifier;
    std::string systemIdentifier;
};

#endif
