#ifndef SEARCH_MOTION_H
#define SEARCH_MOTION_H

#include "model/ptr_cursor.h"
#include "direction.h"
#include "motion.h"
#include "controller/controller.h"


namespace VM {


    template<Direction dir> struct SearchMotion;
    struct SearchWrapper
    {
        enum class State {
            NotFound,
            Found,
            HitTop,
            HitBottom
        };
        Cursor cursor;
        State state;
        template<Direction dir> Cursor unwrap(Controller *c, bool move, const std::string &target) {
            switch (state) {
                case State::HitBottom:
                    c->setMessage("search hit BOTTOM, continuing at TOP");
                    break;
                case State::HitTop:
                    c->setMessage("search hit TOP, continuing at BOTTOM");
                    break;
                case State::NotFound:
                    c->setMessage("E: Pattern not found: "+ target);
                    break;
                case State::Found:
                    if(move)
                    {
                        if(dir == Direction::UP)
                            c->setMessage("?"+target);
                        else if(dir == Direction::DOWN)
                            c->setMessage("/"+target);
                        break;
                    }
                    c->setMessage("");
            }
            return cursor;
        }
    };





    template<> struct SearchMotion<Direction::DOWN>: public ClonableMotion<Motion, SearchMotion<Direction::DOWN>> {
        std::string target;
        char command;
        Controller *controller;
        Cursor nextPosition(const PtrCursor &cursor) override {
            return nextPositionW(cursor).unwrap<Direction::DOWN> (controller, command == '\0', target);
        }
        SearchWrapper nextPositionW(const PtrCursor &cursor) {
            size_t count = 0;
            for(size_t k=0; k<quantifier; ++k) {
                Cursor marker{cursor};
                marker.col = cursor.getLineIterator()->find(target, marker.col+1);
                while(marker.col != std::string::npos) {
                    if(++count == quantifier) return SearchWrapper{marker, SearchWrapper::State::Found};
                    marker.col = cursor.getLineIterator()->find(target, marker.col+1);
                };
                
                marker = Cursor{cursor.getLine()+1, 0};
                for(auto it=cursor.getLineIterator()+1; it!=cursor.getLineEnd(); ++it, ++marker.line) {
                    marker.col = it->find(target, 0);
                    while(marker.col != std::string::npos) {
                        if(++count == quantifier) return SearchWrapper{marker, SearchWrapper::State::Found};
                        marker.col = it->find(target, marker.col+1);
                    };
                }

                marker = Cursor{0, 0};
                for(auto it=cursor.getLineBegin(); it!=cursor.getLineIterator(); ++it, ++marker.line) {
                    marker.col = it->find(target, 0);
                    while(marker.col != std::string::npos) {
                        if(++count == quantifier) return SearchWrapper{marker, SearchWrapper::State::HitBottom};
                        marker.col = it->find(target, marker.col+1);
                    };
                }

                marker.col = cursor.getLineIterator()->find(target, 0);
                while(marker.col <= cursor.getCol()) {
                    if(++count == quantifier) {
                        if(marker.col == cursor.getCol()) --count;
                        else return SearchWrapper{marker, SearchWrapper::State::HitBottom};
                    }
                    marker.col = cursor.getLineIterator()->find(target, marker.col+1);
                };
            }

            return SearchWrapper{cursor, SearchWrapper::State::NotFound};
        }

        SearchMotion(size_t quantifier, const std::string &target, const char &command, Controller *controller):
            Clonable{quantifier},
            target{target},
            command{command},
            controller{controller}
        {}
    };

    template<> struct SearchMotion<Direction::UP>: public ClonableMotion<Motion, SearchMotion<Direction::UP>> {
        std::string target;
        char command;
        Controller *controller;
        Cursor nextPosition(const PtrCursor &cursor) override {
            return nextPositionW(cursor).unwrap<Direction::UP> (controller, command == '\0', target);
        }

        SearchWrapper nextPositionW(const PtrCursor &cursor) {
            size_t count = 0;
            for(size_t k=0; k<quantifier; ++k) {
                Cursor marker{cursor};
                if (marker.col != 0) {
                    marker.col = cursor.getReverseLineIterator()->rfind(target, marker.col - 1);
                    while (marker.col != std::string::npos) {
                        if (++count == quantifier) return SearchWrapper{marker, SearchWrapper::State::Found};
                        marker.col = cursor.getReverseLineIterator()->rfind(target, marker.col - 1);
                    };
                }
                
                marker = Cursor{cursor.getLine()-1, std::string::npos};
                for(auto it=cursor.getReverseLineIterator()+1; it!=cursor.getLineReverseEnd(); ++it, --marker.line) {
                    marker.col = it->rfind(target, std::string::npos);
                    while(marker.col != std::string::npos) {
                        if(++count == quantifier) return SearchWrapper{marker, SearchWrapper::State::Found};
                        marker.col = it->rfind(target, marker.col-1);
                    };
                }

                marker = Cursor{cursor.getBufferSize()-1, std::string::npos};
                for(auto it=cursor.getLineReverseBegin(); it!=cursor.getReverseLineIterator(); ++it, --marker.line) {
                    marker.col = it->rfind(target, std::string::npos);
                    while(marker.col != std::string::npos) {
                        if(++count == quantifier) return SearchWrapper{marker, SearchWrapper::State::HitTop};
                        marker.col = it->rfind(target, marker.col-1);
                    };
                }

                marker.col = cursor.getReverseLineIterator()->rfind(target, std::string::npos);
                while(marker.col >= cursor.getCol() && marker.col < cursor.getReverseLineIterator()->size()) {
                    if(++count == quantifier) {
                        if(marker.col == cursor.getCol()) --count;
                        else return SearchWrapper{marker, SearchWrapper::State::HitTop};
                    }
                    marker.col = cursor.getReverseLineIterator()->rfind(target, marker.col-1);
                };
            }

            return SearchWrapper{cursor, SearchWrapper::State::NotFound};
        }

        SearchMotion(size_t quantifier, const std::string &target, const char &command, Controller *controller):
                Clonable{quantifier},
                target{target},
                command{command},
                controller{controller}
        {}
    };
}

#endif

