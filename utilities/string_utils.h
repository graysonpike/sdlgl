#ifndef SDLGL_STRING_UTILS_H
#define SDLGL_STRING_UTILS_H

#include <string>
#include <vector>

class StringUtils {
   public:
    /**
     * Splits a string into a vector of strings using a given delimiter character.
     * 
     * @param str The input string to split
     * @param delimiter The character to use as a delimiter
     * @return A vector of strings, each representing a part of the original string
     * 
     * Examples:
     *   split("hello,world,test", ',') => {"hello", "world", "test"}
     *   split("a b c", ' ') => {"a", "b", "c"}
     *   split("word", ' ') => {"word"}
     *   split("", ',') => {""}
     */
    static std::vector<std::string> split(const std::string& str, char delimiter);
};

#endif
