#include <HTMLParagraphElement.hpp>

ParagraphElement::ParagraphElement() {
    title = "paragraph";
}
bool ParagraphElement::isParagraphNode() const
{
    return true;
}
