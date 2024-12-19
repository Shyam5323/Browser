#include <HTMLTokenizer.hpp>
#include <HTMLTokenizerUtils.cpp>

#include <algorithm>

std::set<char> spaceChars = {'\u0009', '\u000A', '\u000C', '\u0020'};

bool HTMLTokenizer::containsDoctype(const std::string &htmlString)
{
    return (getStringIposition(htmlString, "<!DOCTYPE") != -1);
}
bool HTMLTokenizer::containsRootElement(const std::string &html_string)
{
    return containsRootOpen(html_string) &&
           containsRootClose(html_string) &&
           containsRootOpenBeforeClose(html_string);
}
bool HTMLTokenizer::containsRootOpen(const std::string &htmlString)
{
    return stringContains(htmlString, "<html ") || stringContains(htmlString, "<html>");
}

bool HTMLTokenizer::containsRootClose(const std::string &htmlString)
{
    return stringContains(htmlString, "</html>");
}

bool HTMLTokenizer::containsRootOpenBeforeClose(const std::string &htmlString)
{
    int openPos = getStringIposition(htmlString, "<html");
    int closePos = getStringIposition(htmlString, "</html>");
    return (openPos != -1 && closePos != -1 && openPos < closePos);
}

bool HTMLTokenizer::doctypeBeforeRoot(const std::string &htmlString)
{
    int doctypePos = getStringIposition(htmlString, "<!DOCTYPE");
    int rootPos = getStringIposition(htmlString, "<html");
    return (doctypePos != -1 && rootPos != -1 && doctypePos < rootPos);
}

bool HTMLTokenizer::isValidHtmlString(const std::string &html_string)
{
    return containsRootElement(html_string) && containsDoctype(html_string) &&
           doctypeBeforeRoot(html_string);
}

std::shared_ptr<HTMLToken> HTMLTokenizer::createTokenFromString(const std::string &htmlString)
{
    tokenizerState currentState = dataState;
    auto it = htmlString.cbegin();
    return createTokenFromString(htmlString, currentState, it);
}
std::shared_ptr<HTMLToken> HTMLTokenizer::createTokenFromString(const std::string &htmlString,
                                                                HTMLTokenizer::tokenizerState &state, std::string::const_iterator &it)
{
    std::shared_ptr<HTMLToken> token = std::make_shared<HTMLToken>();

    for (; it != htmlString.cend(); ++it)
    {
        char nextChar = *it;
        switch (state)
        {
        case dataState:
        {
            if (nextChar == '&')
                state = charRefInDataState;

            else if (nextChar == '<')
                state = tagOpenState;

            else
            {
                token = std::static_pointer_cast<HTMLToken>(std::make_shared<CharacterToken>(nextChar));
                it++;
                return token;
            }

            break;
        }

        case tagOpenState:
        {
            if (nextChar == '!')
                state = markupDeclarationOpenState;

            else if (nextChar == '/')
                state = endTagOpenState;

            else if (isalpha(nextChar))
            {
                token = std::make_shared<StartToken>(nextChar);
                state = tagNameState;
            }

            else if (nextChar == '?')
                state = bogusCommentState;

            break;
        }

        case tagNameState:
        {
            if (spaceChars.count(nextChar) != 0)
                state = beforeAttributeNameState;

            else if (nextChar == '/')
                state = selfClosingStartTagState;

            else if (nextChar == '>')
            {
                state = dataState;
                it++;
                return token;
            }

            else if (isalpha(nextChar))
                token->addCharToTagName(nextChar);

            else
                token->addCharToTagName(nextChar);

            break;
        }

        case charRefInDataState:
            break;

        case selfClosingStartTagState:
        {
            if (nextChar == '>')
            {
                state = dataState;
                token->setSelfClosing(true);
                it++;
                return token;
            }

            break;
        }

        case beforeAttributeNameState:
        {
            if (spaceChars.count(nextChar) != 0)
                break;

            else if (nextChar == '/')
                state = selfClosingStartTagState;

            else if (nextChar == '>')
            {
                state = dataState;
                it++;
                return token;
            }

            else
            {
                state = attributeNameState;
                token->addToCurrentAttributeName(nextChar);
            }

            break;
        }

        case attributeNameState:
        {
            if (spaceChars.count(nextChar) != 0)
                state = afterAttributeNameState;

            else if (nextChar == '/')
                state = selfClosingStartTagState;

            else if (nextChar == '=')
                state = beforeAttributeValueState;

            else
            {
                token->addToCurrentAttributeName(nextChar);
            }

            break;
        }

        case afterAttributeNameState:
        {
            if (spaceChars.count(nextChar) != 0)
                break;

            if (nextChar == '/')
                state = selfClosingStartTagState;

            if (nextChar == '=')
                state = beforeAttributeValueState;

            break;
        }

        case beforeAttributeValueState:
        {
            if (spaceChars.count(nextChar) != 0)
                break;

            else if (nextChar == '"')
                state = attributeValueDoubleQuotedState;

            else if (nextChar == '&')
                state = attributeValueUnquotedState;

            else if (nextChar == '\'')
                state = attributeValueSingleQuotedState;

            else if (nextChar == '>')
            {
                state = dataState;
                it++;
                return token;
            }

            else
            {
                token->addToCurrentAttributeName(nextChar);
                state = attributeValueUnquotedState;
            }

            break;
        }

        case attributeValueDoubleQuotedState:
        {
            if (nextChar == '"')
                state = afterAttributeValueQuotedState;

            else if (nextChar == '&')
                state = charRefInAttributeValueState;

            else
                token->addToCurrentAttributeValue(nextChar);

            break;
        }

        case attributeValueSingleQuotedState:
        {
            if (nextChar == '\'')
                state = afterAttributeValueQuotedState;

            else if (nextChar == '&')
                state = charRefInAttributeValueState;

            else
                token->addToCurrentAttributeValue(nextChar);

            break;
        }

        case attributeValueUnquotedState:
        {
            if (spaceChars.count(nextChar) != 0)
                state = beforeAttributeValueState;

            else if (nextChar == '&')
                state = charRefInAttributeValueState;

            else if (nextChar == '>')
            {
                state = dataState;
                it++;
                return token;
            }

            else
                token->addToCurrentAttributeValue(nextChar);

            break;
        }

        case afterAttributeValueQuotedState:
        {
            token->processCurrentAttribute();

            if (spaceChars.count(nextChar) != 0)
                state = beforeAttributeNameState;

            else if (nextChar == '/')
                state = selfClosingStartTagState;

            else if (nextChar == '>')
            {
                state = dataState;
                it++;
                return token;
            }

            break;
        }

        case bogusCommentState:
            break;

        case markupDeclarationOpenState:
        {
            if (std::string(it, it + 2) == "--")
            {
                it += 1;
                token = std::make_shared<CommentToken>();
                state = commentStartState;
            }

            std::string nextSevenChars(it, it + 7);

            if (getStringIposition(nextSevenChars, "doctype") == 0)
            {
                it += 6;
                state = doctypeState;
            }

            break;
        }

        case doctypeState:
        {
            if (spaceChars.count(nextChar) != 0)
                state = beforeDoctypeNameState;

            else
            {
                it--;
                state = beforeDoctypeNameState;
            }

            break;
        }

        case beforeDoctypeNameState:
        {
            if (spaceChars.count(nextChar) != 0)
                break;

            token = std::static_pointer_cast<HTMLToken>(std::make_shared<DOCTYPEToken>());
            // token = std::make_shared<DOCTYPEToken>();

            if (nextChar == '>')
            {
                state = dataState;
                it++;
                return token;
            }

            else
            {
                token->addCharToTagName(nextChar);
                state = doctypeNameState;
                break;
            }
        }

        case doctypeNameState:
        {
            if (spaceChars.count(nextChar) != 0)
            {
                state = afterDoctypeNameState;
                token->setIsNameSet(true);
                break;
            }

            else if (nextChar == '>')
            {
                state = dataState;
                token->setIsNameSet(true);
                it++;
                return token;
            }

            token->addCharToTagName(nextChar);
            break;
        }

        case afterDoctypeNameState:
        {
            if (spaceChars.count(nextChar) != 0)
                break;

            state = bogusDoctypeState;

            break;
        }

        case bogusDoctypeState:
        {
            if (nextChar == '>')
            {
                state = dataState;
                it++;
                return token;
            }

            break;
        }

        case endTagOpenState:
        {
            if (isalpha(nextChar))
            {
                token = std::make_shared<EndToken>(nextChar);
                state = tagNameState;
            }
            break;
        }

        case commentStartState:
        {
            if (nextChar == '-')
            {
                state = commentStartDashState;
            }
            else if (nextChar == '>')
            {
                state = dataState;
                it++;
                return token;
            }
            else
            {
                token->addCharToData(nextChar);
                state = commentState;
            }
            break;
        }
        case commentStartDashState:
        {
            if (nextChar == '-')
                state = commentEndState;

            else if (nextChar == '>')
            {
                state = dataState;
                it++;
                return token;
            }

            // EOF: parse error

            else
            {
                token->addCharToData('-');
                token->addCharToData(nextChar);
                state = commentState;
            }

            break;
        }

        case commentState:
        {
            if (nextChar == '-')
                state = commentEndDashState;

            // null, EOF: parse error

            else
                token->addCharToData(nextChar);

            break;
        }

        case commentEndDashState:
        {
            if (nextChar == '-')
                state = commentEndState;

            else
            {
                token->addCharToData('-');
                token->addCharToData(nextChar);
                state = commentState;
            }

            break;
        }

        case commentEndState:
        {
            if (nextChar == '>')
            {
                state = dataState;
                it++;
                return token;
            }

            // parse error
            else if (nextChar == '!')
                state = commentEndBangState;

            else if (nextChar == '-')
                token->addCharToData(nextChar);

            else
            {
                token->addCharToData('-');
                token->addCharToData('-');
                token->addCharToData(nextChar);
                state = commentState;
            }

            break;
        }

        case commentEndBangState:
        {
            if (nextChar == '-')
            {
                token->addCharToData('-');
                token->addCharToData('-');
                token->addCharToData('!');
                state = commentEndDashState;
            }

            else if (nextChar == '>')
            {
                state = dataState;
                it++;
                return token;
            }

            // null, EOF: parse error

            else
            {
                token->addCharToData('-');
                token->addCharToData('-');
                token->addCharToData('!');
                token->addCharToData(nextChar);
                state = commentState;
            }

            break;
        }

        default:
        {
            break;
        }
        }
    }
}

std::vector<std::shared_ptr<HTMLToken>> HTMLTokenizer::tokenizeString(const std::string &htmlString)
{
    auto it = htmlString.cbegin();
    tokenizerState state = dataState;

    std::shared_ptr<HTMLToken> token = createTokenFromString(htmlString, state, it);

    std::vector<std::shared_ptr<HTMLToken>> tokens;

    while (!(it >= htmlString.cend()))
    {
        tokens.push_back(token);
        token = createTokenFromString(htmlString, state, it);
    }
    if (it == htmlString.cend())
    {
        tokens.push_back(token);
    }
    return tokens;
}