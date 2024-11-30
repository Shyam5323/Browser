#include <HTMLelement.hpp>

Element::Element() {
    title = "";
    id = "";
    childs = {};
}
Element::Element(Element& element) {
    this->title = element.getTitle();
    this->id = element.getId();
    this->childs = element.getChilds();
}
Element::~Element() {}

std::string Element::getId() {
    return id;
}

std::string Element::getTitle() {
    return title;
}

std::vector<std::shared_ptr<Element>> Element::getChilds() {
    return childs;
}

void Element::setId(const std::string& id) {
    this->id = id;
}

void Element::setTitle(const std::string& title) {
    this->title = title;
}

void Element::addChild(std::shared_ptr<Element>& element) {
    childs.push_back(element);
}

void Element::addText(std::shared_ptr<Element>& textNode) {
    if (childs.size() > 0 && childs.back()->isTextNode())
        childs.back()->addChar(textNode->getText());
    else
        addChild(textNode);
    
}