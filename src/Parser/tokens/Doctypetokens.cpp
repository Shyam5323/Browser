#include <Doctypetokens.hpp>

DOCTYPEToken::DOCTYPEToken()
{
    nameSet = false;
    publicIdentifierSet = false;
    systemIdentifierSet = false;
}

DOCTYPEToken::DOCTYPEToken(char name)
{
    nameSet = false;
    publicIdentifierSet = false;
    systemIdentifierSet = false;
    tagName = tolower(name); // Assuming tagName is a member variable
}

bool DOCTYPEToken::isDoctypeToken() const
{
    return true;
}

void DOCTYPEToken::setIsNameSet(bool isSet)
{
    nameSet = isSet;
}

bool DOCTYPEToken::isNameSet() const
{
    return nameSet;
}

bool DOCTYPEToken::isPublicIdentifierSet() const
{
    return publicIdentifierSet;
}

bool DOCTYPEToken::isSystemIdentifierSet() const
{
    return systemIdentifierSet;
}

std::string DOCTYPEToken::getPublicIdentifier() const
{
    return publicIdentifier;
}

std::string DOCTYPEToken::getSystemIdentifier() const
{
    return systemIdentifier;
}
