#ifndef HTMLTOKEN_HPP
#define HTMLTOKEN_HPP
#include <HTMLtokens.hpp>

class CharacterToken : HTMLToken
{
    CharacterToken(char name);
    bool isCharToken() const;
    char getChar() const;
    void setChar(const char &name);

private:
    char tokenChar;
};

#endif