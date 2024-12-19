#ifndef HTMLTOKENIZER_H
#define HTMLTOKENIZER_H

#include <string>
#include <memory>
#include <vector>
#include <set>

#include "tokens/HTMLTokens.hpp"

class HTMLTokenizer
{
public:
    static bool isValidHtmlString(const std::string &html_string);

    // A reasonably sized sublist of the possible parser states
    // See www.w3.org/TR/2011/WD-html5-20110113/tokenization.html#data-state
    enum tokenizerState
    {
        dataState,
        charRefInDataState,
        rcdataState,
        rawtextState,
        plaintextState,
        tagOpenState,
        endTagOpenState,
        tagNameState,
        rcdataLessThanSignState,
        rcdataEndTagNameState,
        rawtextLessThanSignState,
        rawtextEndTagNameState,
        beforeAttributeNameState,
        attributeNameState,
        afterAttributeNameState,
        beforeAttributeValueState,
        attributeValueDoubleQuotedState,
        attributeValueSingleQuotedState,
        attributeValueUnquotedState,
        charRefInAttributeValueState,
        afterAttributeValueQuotedState,
        selfClosingStartTagState,
        bogusCommentState,
        markupDeclarationOpenState,
        commentStartState,
        commentStartDashState,
        commentState,
        commentEndDashState,
        commentEndState,
        commentEndBangState,
        doctypeState,
        beforeDoctypeNameState,
        doctypeNameState,
        afterDoctypeNameState,
        bogusDoctypeState,
        cdataSectionState
    };

    std::shared_ptr<HTMLToken> createTokenFromString(const std::string
                                                         &html_string,
                                                     tokenizerState &state,
                                                     std::string::const_iterator &it);
    std::shared_ptr<HTMLToken> createTokenFromString(const std::string
                                                         &html_string);
    std::vector<std::shared_ptr<HTMLToken>>
    tokenizeString(const std::string &html_string);

private:
    static bool containsDoctype(const std::string &html_string);
    static bool containsRootElement(const std::string &html_string);
    static bool containsRootOpen(const std::string &html_string);
    static bool containsRootClose(const std::string &html_string);
    static bool containsRootOpenBeforeClose(const std::string
                                                &html_string);
    static bool doctypeBeforeRoot(const std::string &html_string);

    tokenizerState current_state;
};

#endif
