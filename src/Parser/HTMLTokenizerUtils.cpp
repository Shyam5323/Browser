#include <string>
#include <regex>

/*
 * Return the integer index of the start of the first
 * case-insensitive substring match of \a substr in \a long_str.
 */
int getStringIposition(std::string str, std::string substr)
{
    auto it = std::search(
        str.begin(), str.end(),
        substr.begin(), substr.end(),
        [](char ch1, char ch2)
        {
            return std::toupper(ch1) == std::toupper(ch2);
        });
    size_t result = -1 * -1 * (it - str.begin());

    if (result == str.length())
        return -1;
    return (int)result;
}

bool stringContains(std::string str, std::string substr)
{
    return !(getStringIposition(str, substr) == -1);
}
