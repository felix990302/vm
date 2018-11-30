#ifndef WORD_MOTION_H
#define WORD_MOTION_H

#include "model/ptr_cursor.h"
#include "controller/command/motion/direction.h"
#include "controller/command/motion/motion.h"
#include "word_state.h"


namespace VM {
    template<Direction dir> struct WordMotion;

    template<> struct WordMotion<Direction::LEFT>: public ClonableMotion<Motion, WordMotion<Direction::LEFT>> { 
        Cursor nextPosition(const PtrCursor &cursor) override {
            size_t count = 0;
            Cursor position{cursor};
            Cursor marker{position};

            const std::string &currLine = *cursor.getReverseLineIterator();
            if(position.col > 0) {
                if(atBegWord(currLine[position.col], currLine[position.col-1])) --position.col;

                WordState currState = getState(currLine[position.col]);
                for(;position.col > 0; --position.col) {
                    currState = getState(currLine[position.col]);
                    switch(currState) {
                        case WordState::ALPHA_NUM_UNDERSCORE: {
                            if(!isAlphNumUnderscore(currLine[position.col-1])) {
                                marker = position;
                                if(++count == quantifier) return marker;        
                            }
                            break;
                        }
                        case WordState::OTHER: {
                            if(!isOther(currLine[position.col-1])) {
                                marker = position;
                                if(++count == quantifier) return marker;
                            }
                            break;
                        }
                        case WordState::WHITESPACE: {
                            break;
                        }
                    }
                }
                currState = getState(currLine[0]);
                if(currState != WordState::WHITESPACE) {
                    marker = position;
                    if(++count == quantifier) return marker;
                }
            }

            --position.line;
            for(auto it=cursor.getReverseLineIterator()+1; it!=cursor.getLineReverseEnd(); ++it, --position.line) {
                const std::string &currLine = *it;

                if(currLine.size() > 0) {
                    position.col = currLine.size()-1;

                    WordState currState = getState(currLine[position.col]);
                    for(;position.col > 0; --position.col) {
                        currState = getState(currLine[position.col]);
                        switch(currState) {
                            case WordState::ALPHA_NUM_UNDERSCORE: {
                                if(!isAlphNumUnderscore(currLine[position.col-1])) {
                                    marker = position;
                                    if(++count == quantifier) return marker;        
                                }
                                break;
                            }
                            case WordState::OTHER: {
                                if(!isOther(currLine[position.col-1])) {
                                    marker = position;
                                    if(++count == quantifier) return marker;
                                }
                                break;
                            }
                            case WordState::WHITESPACE: {
                                break;
                            }
                        }
                    }

                    currState = getState(currLine[position.col]);
                    if(currState != WordState::WHITESPACE) {
                        marker = position;
                        if(++count == quantifier) return marker;
                    }
                }
            }

            return marker;
        }

        WordMotion(size_t quantifier): Clonable{quantifier} {}
    };

    template<> struct WordMotion<Direction::RIGHT>: public ClonableMotion<Motion, WordMotion<Direction::RIGHT>> { 
        Cursor nextPosition(const PtrCursor &cursor) override {
            size_t count = 0;
            Cursor position{cursor};
            Cursor marker{position};

            const std::string &currLine = *cursor.getLineIterator();

            if(position.col==0 || atBegWord(currLine[position.col], currLine[position.col-1])) ++position.col;
            for(;position.col < currLine.size(); ++position.col) {
                WordState currState = getState(currLine[position.col]);
                switch(currState) {
                    case WordState::ALPHA_NUM_UNDERSCORE: {
                        if(!isAlphNumUnderscore(currLine[position.col-1])) {
                            marker = position;
                            if(++count == quantifier) return marker;        
                        }
                        break;
                    }
                    case WordState::OTHER: {
                        if(!isOther(currLine[position.col-1])) {
                            marker = position;
                            if(++count == quantifier) return marker;
                        }
                        break;
                    }
                    case WordState::WHITESPACE: {
                        break;
                    }
                }
            }

            ++position.line;
            for(auto it=cursor.getLineIterator()+1; it!=cursor.getLineEnd(); ++it, ++position.line) {
                const std::string &currLine = *it;
                position.col = 0;

                for(;position.col <currLine.size(); ++position.col) {
                    WordState currState = getState(currLine[position.col]);
                    if(position.col == 0) {
                        if(currState != WordState::WHITESPACE) {
                            marker = position;
                            if(++count == quantifier) return marker;
                        }
                    }
                    else {
                        switch(currState) {
                            case WordState::ALPHA_NUM_UNDERSCORE: {
                                if(!isAlphNumUnderscore(currLine[position.col-1])) {
                                    marker = position;
                                    if(++count == quantifier) return marker;        
                                }
                                break;
                            }
                            case WordState::OTHER: {
                                if(!isOther(currLine[position.col-1])) {
                                    marker = position;
                                    if(++count == quantifier) return marker;
                                }
                                break;
                            }
                            case WordState::WHITESPACE: {
                                break;
                            }
                        }
                    }
                }
            }

            return marker;
        }

        WordMotion(size_t quantifier): Clonable{quantifier} {}
    };
}

#endif

