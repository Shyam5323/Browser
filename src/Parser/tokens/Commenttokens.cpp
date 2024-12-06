#include <Commenttokens.hpp>

CommentToken::CommentToken()
{
}
bool CommentToken::isCommentToken() const
{
    return true;
}
std::string CommentToken::getData() const
{
    return data;
}
void CommentToken::addCharToData(char nextChar)
{
    data += nextChar;
}
void CommentToken::setData(std::string data)
{
    this->data = data;
}