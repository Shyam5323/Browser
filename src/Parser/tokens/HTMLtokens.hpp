#ifndef HTMLTOKENS_H
#define HTMLTOKENS_H

#include <string>
#include <map>
#include <Charactertokens.hpp>
#include <Commenttokens.hpp>
#include <Doctypetokens.hpp>
#include <Endtokens.hpp>
#include <Starttokens.hpp>

class HTMLToken
{
public:
    // General HTMLToken properties
    virtual ~HTMLToken();
    std::string getTagName() const;
    void addCharToTagName(char nextChar);
    void setTagName(std::string name);

    // Doctype Token functions
    virtual bool isDoctypeToken() const { return false; }
    virtual bool isStartToken() const { return false; }
    virtual bool isEndToken() const { return false; }
    virtual void setIsNameSet(bool isSet) {}
    virtual bool isNameSet() const { return false; }
    virtual bool isPublicIdentifierSet() const { return false; }
    virtual bool isSystemIdentifierSet() const { return false; }
    virtual std::string getPublicIdentifier() const { return ""; }
    virtual std::string getSystemIdentifier() const { return ""; }

    // Start and End Token functions
    virtual bool isSelfClosing() const { return false; }
    virtual void setSelfClosing(bool closing) {}
    virtual std::map<std::string, std::string> getAttributes() const { return {}; }
    virtual void addToCurrentAttributeName(char nextChar) {}
    virtual void addToCurrentAttributeValue(char nextChar) {}
    virtual std::string getAttributeValue(const std::string &attributeName) const { return ""; }
    virtual bool containsAttribute(const std::string &attributeName) const { return false; }
    virtual void processCurrentAttribute() {}

    // Comment Token functions
    virtual bool isCommentToken() const { return false; }
    virtual std::string getData() const { return ""; }
    virtual void addCharToData(char nextChar) {}
    virtual void setData(const std::string &dataString) {}

    // Character Token functions
    virtual bool isCharToken() const { return false; }
    virtual char getChar() const { return '\0'; };
    virtual void setChar(const char &charToSet) {}

protected:
    std::string tagName;
};

#endif
