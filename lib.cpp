#include "lib.h"
#include <regex>

std::string removePunctuation(const std::string& word) {
    std::string result;
    for (char c : word) {
        if (isalnum(c) || c == '\'') {
            result += tolower(c);
        }
    }
    return result;
}

std::vector<std::string> extractURLs(const std::string& text) {
    std::vector<std::string> urls;
    std::regex urlRegex("(https?|ftp):\\/\\/(www\\.)?[-a-zA-Z0-9@:%._\\+~#=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");
    std::sregex_iterator iter(text.begin(), text.end(), urlRegex);
    std::sregex_iterator end;
    while (iter != end) {
        urls.push_back(iter->str());
        ++iter;
    }
    return urls;
}
