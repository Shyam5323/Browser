#include <Endtokens.hpp>

EndToken::EndToken()
{
    selfClosing = false;
}
EndToken::EndToken(char token_name)
{
    tagName = towlower(token_name);
}
bool EndToken::isSelfClosing() const
{
    return selfClosing;
}
void EndToken::setSelfClosing(bool closing)
{
    selfClosing = closing;
}
std::map<std::string, std::string> EndToken::getAttributes() const
{
    std::wcerr << "PARSE ERROR: Attempt to access attributes " << " in end token" << std::endl;
    return {};
}
void EndToken::addToCurrentAttributeName(char next_char)
{
    return;
}
void EndToken::addToCurrentAttributeValue(char next_char)
{
    return;
}
std::string EndToken::getAttributeValue(std::string attribute_name) const
{
    std::wcerr << "PARSE ERROR: Attempt to access attribute " << attribute_name << " in end token" << std::endl;
    return NULL;
}
bool EndToken::containsAttribute(std::string attribute_name) const
{
    return false;
}
void EndToken::processCurrentAttribute()
{
    return;
}
bool EndToken::isEndToken() const
{
    return true;
}