#ifndef COMMENTTOKEN_H
#define COMMENTTOKEN_H

#include <HTMLtokens.hpp>

class CommentToken : public HTMLToken
{
public:
    CommentToken();
    bool isCommentToken() const;
    std::string getData() const;
    void addCharToData(char nextChar);
    void setData(std::string dataString);

protected:
    std::string data;
};

#endif
