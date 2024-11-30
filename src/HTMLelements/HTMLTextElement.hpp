#ifndef HTMLTEXTELEMENT_H
#define HTMLTEXTELEMENT_H

#include <HTMLelement.hpp>

class TextElement : Element {
    TextElement();
    bool isTextNode() const { return true; }
    void addChar(const char &next_char);
    void addChar(const std::string &next_char);
    std::string getText() const;

protected:
    std::string text;
};

#endif