#include <HTMLtokens.hpp>

HTMLToken::~HTMLToken() {}

std::string HTMLToken::getTagName() const
{
    return tagName;
}

void HTMLToken::addCharToTagName(char next_c)
{
    tagName += next_c;
}

void HTMLToken::setTagName(std::string tag_name)
{
    this->tagName = tag_name;
}