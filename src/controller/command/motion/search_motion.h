#ifndef SEARCH_MOTION_H
#define SEARCH_MOTION_H

#include <regex>
#include "model/ptr_cursor.h"
#include "direction.h"
#include "motion.h"


namespace VM {
    template<Direction dir> struct SearchMotion;

    template<> struct SearchMotion<Direction::DOWN>: public Motion {
        std::string target;
        std::regex regexTarget {target};
        std::smatch regexMatch;

        Cursor nextPosition(const PtrCursor &cursor) override {
            Cursor next {cursor};

            std::string temp = cursor.getLineIterator()->substr(cursor.col + 1);
            if(std::regex_search(temp, regexMatch, regexTarget)) {
                next.col = cursor.getLineIterator()->find(regexMatch[0], cursor.col+1);
                return next;
            }
            for(auto it=cursor.getLineIterator()+1; it!=cursor.buffer.end(); ++it, ++next.line) {
                if(std::regex_match(*it, regexMatch, regexTarget)) {
                    next.col = it->find(regexMatch[0]);
                    return next;
                }
            }
            next.line = 0;
            for(auto it=cursor.buffer.begin(); it!=cursor.getLineIterator()+1; ++it, ++next.line) {
                if(std::regex_match(*it, regexMatch, regexTarget)) {
                    next.col = it->find(regexMatch[0]);
                    return next;
                }
            }

            return cursor;
        }

        std::unique_ptr<Motion> clone() override {
            return std::make_unique<SearchMotion>(*this);
        }

        SearchMotion(int quantifier, const std::string &target):
            Motion{quantifier},
            target{target},
            regexTarget{target},
            regexMatch{}
        {}
    };

    template<> struct SearchMotion<Direction::UP>: public Motion {
        std::string target;
        std::regex regexTarget {target};
        std::smatch regexMatch;

        Cursor nextPosition(const PtrCursor &cursor) override {
            Cursor next {cursor};

            if(std::regex_search(*cursor.getLineIterator(), regexMatch, regexTarget)) {
                for(size_t k=regexMatch.size()-1; k>=0 ; --k) {
                    next.col = cursor.getReverseLineIterator()->find(regexMatch[regexMatch.size() - 1]);
                    size_t temp = cursor.getReverseLineIterator()->find(regexMatch[k], cursor.col+1);
                    while(temp != std::string::npos && temp < cursor.col) {
                        next.col = temp;
                        temp = cursor.getReverseLineIterator()->find(regexMatch[regexMatch.size() - 1], temp+1);
                    }
                    if(next.col < cursor.col) return next;
                }
            }
            for(auto it=cursor.getReverseLineIterator()+1; it!=cursor.buffer.rend(); ++it, --next.line) {
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
            for(auto it=cursor.buffer.rbegin(); it!=cursor.getReverseLineIterator()+1; ++it, --next.line) {
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

            return cursor;
        }

        std::unique_ptr<Motion> clone() override {
            return std::make_unique<SearchMotion>(*this);
        }

        SearchMotion(int quantifier, const std::string &target):
            Motion{quantifier},
            target{target},
            regexTarget{target},
            regexMatch{}
        {}
    };
}

#endif

