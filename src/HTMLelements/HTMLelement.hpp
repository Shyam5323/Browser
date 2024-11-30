#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <string>
#include <vector>
#include <memory>

class Element{
protected:
    std::string title;
    std::string id;
    std::vector<std::shared_ptr<Element>> childs;

public:
    Element();
    Element(Element& element);
    virtual ~Element();
    
    std::string getTitle();
    std::string getId();
    std::vector<std::shared_ptr<Element>> getChilds();
    void setTitle(const std::string& title);
    void setId(const std::string& id);
    void addChild(std::shared_ptr<Element>& element);
    void addText(std::shared_ptr<Element>& textNode);

    virtual bool isTextNode() const { return false; };
    virtual void addChar(const char &next_char) {};
    virtual void addChar(const std::string &next_char) {};
    virtual char getChar() const { return '\0'; };
    virtual std::string getText() const { return ""; };

    virtual bool isParagraphNode() const {return false; }
};

#endif