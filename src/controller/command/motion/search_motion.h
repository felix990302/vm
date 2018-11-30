#ifndef SEARCH_MOTION_H
#define SEARCH_MOTION_H

#include "model/ptr_cursor.h"
#include "direction.h"
#include "motion.h"


namespace VM {
    template<Direction dir> struct SearchMotion;

    template<> struct SearchMotion<Direction::DOWN>: public ClonableMotion<Motion, SearchMotion<Direction::DOWN>> {
        std::string target;

        Cursor nextPosition(const PtrCursor &cursor) override {
            size_t count = 0;
            for(size_t k=0; k<quantifier; ++k) {
                Cursor marker{cursor};
                marker.col = cursor.getLineIterator()->find(target, marker.col+1);
                while(marker.col != std::string::npos) {
                    if(++count == quantifier) return marker;
                    marker.col = cursor.getLineIterator()->find(target, marker.col+1);
                };
                
                marker = Cursor{cursor.getLine()+1, 0};
                for(auto it=cursor.getLineIterator()+1; it!=cursor.getLineEnd(); ++it, ++marker.line) {
                    marker.col = it->find(target, 0);
                    while(marker.col != std::string::npos) {
                        if(++count == quantifier) return marker;
                        marker.col = it->find(target, marker.col+1);
                    };
                }

                marker = Cursor{0, 0};
                for(auto it=cursor.getLineBegin(); it!=cursor.getLineIterator(); ++it, ++marker.line) {
                    marker.col = it->find(target, 0);
                    while(marker.col != std::string::npos) {
                        if(++count == quantifier) return marker;
                        marker.col = it->find(target, marker.col+1);
                    };
                }

                marker.col = cursor.getLineIterator()->find(target, 0);
                while(marker.col < cursor.getCol()) {
                    if(++count == quantifier) return marker;
                    marker.col = cursor.getLineIterator()->find(target, marker.col+1);
                };
            }

            return cursor;
        }

        SearchMotion(size_t quantifier, const std::string &target):
            Clonable{quantifier},
            target{target}
        {}
    };

    template<> struct SearchMotion<Direction::UP>: public ClonableMotion<Motion, SearchMotion<Direction::UP>> {
        std::string target;

        Cursor nextPosition(const PtrCursor &cursor) override {
            size_t count = 0;
            for(size_t k=0; k<quantifier; ++k) {
                Cursor marker{cursor};
                marker.col = cursor.getReverseLineIterator()->rfind(target, marker.col-1);
                while(marker.col != std::string::npos) {
                    if(++count == quantifier) return marker;
                    marker.col = cursor.getReverseLineIterator()->rfind(target, marker.col-1);
                };
                
                marker = Cursor{cursor.getLine()-1, std::string::npos};
                for(auto it=cursor.getReverseLineIterator()+1; it!=cursor.getLineReverseEnd(); ++it, --marker.line) {
                    marker.col = it->rfind(target, std::string::npos);
                    while(marker.col != std::string::npos) {
                        if(++count == quantifier) return marker;
                        marker.col = it->rfind(target, marker.col-1);
                    };
                }

                marker = Cursor{cursor.getBufferSize()-1, std::string::npos};
                for(auto it=cursor.getLineReverseBegin(); it!=cursor.getReverseLineIterator(); ++it, --marker.line) {
                    marker.col = it->rfind(target, std::string::npos);
                    while(marker.col != std::string::npos) {
                        if(++count == quantifier) return marker;
                        marker.col = it->rfind(target, marker.col-1);
                    };
                }

                marker.col = cursor.getReverseLineIterator()->rfind(target, std::string::npos);
                while(marker.col > cursor.getCol() && marker.col < cursor.getReverseLineIterator()->size()) {
                    if(++count == quantifier) return marker;
                    marker.col = cursor.getReverseLineIterator()->rfind(target, marker.col-1);
                };
            }

            return cursor;
        }

        SearchMotion(size_t quantifier, const std::string &target):
            Clonable{quantifier},
            target{target}
        {}
    };
}

#endif

