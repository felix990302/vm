#ifndef BRACE_MATCH_H
#define BRACE_MATCH H

#include <unordered_map>


namespace VM {
    static const std::unordered_map<char, char> OpenBraceMatch {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'},
    };

    static const std::unordered_map<char, char> CloseBraceMatch {
        {')', '('},
        {']', '['},
        {'}', '{'},
    };
}

#endif
