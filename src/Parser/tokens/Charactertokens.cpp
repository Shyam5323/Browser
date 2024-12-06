#include <Charactertokens.hpp>
CharacterToken::CharacterToken(char name)
{
    tokenChar = name;
}
bool CharacterToken::isCharToken() const
{
    return true;
}
void CharacterToken::setChar(const char &name)
{
    tokenChar = name;
}
char CharacterToken::getChar() const
{
    return tokenChar;
}