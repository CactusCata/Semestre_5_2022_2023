#include "utils.hpp"

unsigned int getLength(const char *chars) {
    unsigned int length = 0;
    for (; chars[length] != '\0'; length++);
    return length;
}

std::string charsToString(const char *chars) {
    std::string converted;
    unsigned int size = getLength(chars);
    for (unsigned int i = 0; i < size; i++) {
        converted.push_back(chars[i]);
    }
    return converted;
}

std::string erase(const std::string &str, const char &wanted) {
    std::string erased;
    size_t sizeStr = str.length();
    for (size_t i = 0; i < sizeStr; i++) {
        if (str[i] != wanted) {
          erased.push_back(str[i]);
        }
    }
    return erased;
}
