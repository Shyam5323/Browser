#ifndef DOCUMENTTYPE_H
#define DOCUMENTTYPE_H

#include <string>

class DocumentType {
public:
    DocumentType(const std::string& type) {
        this->type = type;
    }
    DocumentType() {};
    void setType(const std::string& type) {
        this->type = type;
    }
    std::string getType() {
        return type;
    }
protected:
    std::string type;
};

#endif