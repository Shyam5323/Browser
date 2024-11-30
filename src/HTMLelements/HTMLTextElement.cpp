#include <HTMLTextElement.hpp>

TextElement::TextElement() {
    text = "";
    title = "text";
}

void TextElement::addChar(const char &next_char) {
    text += next_char;
}   

void TextElement::addChar(const std::string &next_char){
    text += next_char;
}

std::string TextElement::getText() const {
    return text;
}