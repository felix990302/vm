#ifndef WORD_STATE_H
#define WORD_STATE_H

#include <cctype>


namespace VM {
    enum class WordState {
        ALPHA_NUM_UNDERSCORE,
        WHITESPACE,
        OTHER,
    };

    bool isAlphNumUnderscore(char c) {
        return std::isalnum(c) || c=='_';
    }

    bool isWhiteSpace(char c) {
        return std::isspace(c);
    }

    bool isOther(char c) {
        return !isWhiteSpace(c) && !isAlphNumUnderscore(c);
    }

    WordState getState(char c) {
        if(isAlphNumUnderscore(c)) return WordState::ALPHA_NUM_UNDERSCORE;
        else if(isWhiteSpace(c)) return WordState::WHITESPACE;
        else return WordState::OTHER;
    }

    bool atMidWord(char c, char prev) {
        return
            (isAlphNumUnderscore(c) && isAlphNumUnderscore(prev)) ||
            (isOther(c) && isOther(prev));
    }

    bool atBegWord(char c, char prev) {
        return
            (isAlphNumUnderscore(c) && !isAlphNumUnderscore(prev)) ||
            (isOther(c) && !isOther(prev));
    }
}

#endif

