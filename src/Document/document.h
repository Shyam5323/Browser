#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <list>
#include <memory>
#include <HTMLelement.hpp>
#include <documentType.h>

class Document {
    Document() {
    };
    void addElement(std::shared_ptr<Element> element) {
        elements.emplace_back(element);
    }
    std::list<std::shared_ptr<Element>> getElements() {
        return elements;
    }
    void setDocumentType(const std::string& type) {
        docType.setType(type);
    }
    std::string getDocumentType() {
        return docType.getType();
    }

protected:
    std::list<std::shared_ptr<Element>> elements;
    DocumentType docType;
};

#endif