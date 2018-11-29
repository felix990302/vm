#ifndef SEARCH_MOTION_H
#define SEARCH_MOTION_H

#include <regex>
#include "model/ptr_cursor.h"
#include "direction.h"
#include "motion.h"


namespace VM {
    template<Direction dir> struct SearchMotion;

    template<> struct SearchMotion<Direction::DOWN>: public ClonableMotion<Motion, SearchMotion<Direction::DOWN>> {
        std::string target;
        std::regex regexTarget {target};
        std::smatch regexMatch;

        Cursor nextPosition(const PtrCursor &cursor) override {
            Cursor next {cursor};

            for(size_t i=0; i<quantifier; ++i) {
                std::string temp = cursor.getLineIterator()->substr(cursor.getCol() + 1);
                if(std::regex_search(temp, regexMatch, regexTarget)) {
                    next.col = cursor.getLineIterator()->find(regexMatch[0], cursor.getCol()+1);
                    return next;
                }
                for(auto it=cursor.getLineIterator()+1; it!=cursor.getLineEnd(); ++it, ++next.line) {
                    if(std::regex_match(*it, regexMatch, regexTarget)) {
                        next.col = it->find(regexMatch[0]);
                        return next;
                    }
                }
                next.line = 0;
                for(auto it=cursor.getLineBegin(); it!=cursor.getLineIterator()+1; ++it, ++next.line) {
                    if(std::regex_match(*it, regexMatch, regexTarget)) {
                        next.col = it->find(regexMatch[0]);
                        return next;
                    }
                }
            }

            return cursor;
        }

        SearchMotion(size_t quantifier, const std::string &target):
            Clonable{quantifier},
            target{target},
            regexTarget{target},
            regexMatch{}
        {}
    };

    template<> struct SearchMotion<Direction::UP>: public ClonableMotion<Motion, SearchMotion<Direction::UP>> {
        std::string target;
        std::regex regexTarget {target};
        std::smatch regexMatch;

        Cursor nextPosition(const PtrCursor &cursor) override {
            Cursor next {cursor};

            for(size_t i=0; i<quantifier; ++i) {
                if(std::regex_search(*cursor.getLineIterator(), regexMatch, regexTarget)) {
                    for(int k=regexMatch.size()-1; k>=0 ; --k) {
                        next.col = cursor.getReverseLineIterator()->find(regexMatch[regexMatch.size() - 1]);
                        size_t temp = cursor.getReverseLineIterator()->find(regexMatch[k], cursor.getCol()+1);
                        while(temp != std::string::npos && temp < cursor.getCol()) {
                            next.col = temp;
                            temp = cursor.getReverseLineIterator()->find(regexMatch[regexMatch.size() - 1], temp+1);
                        }
                        if(next.col < cursor.getCol()) return next;
                    }
                }
                for(auto it=cursor.getReverseLineIterator()+1; it!=cursor.getLineReverseEnd(); ++it, --next.line) {
                    if(std::regex_match(*it, regexMatch, regexTarget)) {
                        next.col = it->find(regexMatch[regexMatch.size() - 1]);
                        size_t temp = it->find(regexMatch[regexMatch.size() - 1], next.col+1);
                        while(temp != std::string::npos) {
                            next.col = temp;
                            temp = it->find(regexMatch[regexMatch.size() - 1], temp+1);
                        }
                        return next;
                    }
                }
                next.line = 0;
                for(auto it=cursor.getLineReverseBegin(); it!=cursor.getReverseLineIterator()+1; ++it, --next.line) {
                    if(std::regex_match(*it, regexMatch, regexTarget)) {
                        next.col = it->find(regexMatch[regexMatch.size() - 1]);
                        size_t temp = next.col;
                        while(temp != std::string::npos) {
                            next.col = temp;
                            temp = it->find(regexMatch[regexMatch.size() - 1], temp+1);
                        }
                        return next;
                    }
                }
            }

            return cursor;
        }

        SearchMotion(size_t quantifier, const std::string &target):
            Clonable{quantifier},
            target{target},
            regexTarget{target},
            regexMatch{}
        {}
    };
}

#endif

