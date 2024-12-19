#include <Starttokens.hpp>

StartToken::StartToken()
{
    selfClosing = false;
    currentAttributeName = "";
    currentAttributeValue = "";
    attributes = {};
}
StartToken::StartToken(char tokenName)
{
    tagName = tolower(tokenName);
    selfClosing = false;
    currentAttributeName = "";
    currentAttributeValue = "";
    attributes = {};
}
bool StartToken::isSelfClosing() const
{
    return selfClosing;
}
void StartToken::setSelfClosing(bool val)
{
    selfClosing = val;
}
std::map<std::string, std::string> StartToken::getAttributes() const
{
    return attributes;
}
void StartToken::addToCurrentAttributeName(char next_char)
{
    currentAttributeName += next_char;
}
void StartToken::addToCurrentAttributeValue(char next_char)
{
    currentAttributeValue += next_char;
}
std::string StartToken::getAttributeValue(std::string attribute_name) const
{
    try
    {
        if (containsAttribute(attribute_name) != 0)
            return attributes.at(attribute_name);
        else
            throw attribute_name;
    }
    catch (std::string illegal_name)
    {
        std::wcerr << "TOKENIZATION ERROR: Attempt to access unset "
                   << " attribute name " << illegal_name << std::endl;
        return "";
    }
}
bool StartToken::containsAttribute(std::string attribute_name) const
{
    return (attributes.count(attribute_name) > 0);
}
void StartToken::processCurrentAttribute()
{
    if (containsAttribute(currentAttributeName))
        return;

    attributes.insert({currentAttributeName, currentAttributeValue});

    currentAttributeName = "";
    currentAttributeValue = "";
};
bool StartToken::isStartToken() const
{
    return true;
};