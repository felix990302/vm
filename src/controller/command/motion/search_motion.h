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
            Cursor next {cursor};

            next.col = cursor.getLineIterator()->find(target, cursor.getCol()+1);
            if(next.col != std::string::npos) return next;

            ++next.line;
            for(auto it=cursor.getLineIterator()+1; it!=cursor.getLineEnd(); ++it, ++next.line) {
                next.col = it->find(target);
                if(next.col != std::string::npos) return next;
            }

            next.line = 0;
            for(auto it=cursor.getLineBegin(); it!=cursor.getLineIterator()+1; ++it, ++next.line) {
                next.col = it->find(target);
                if(next.col != std::string::npos) return next;
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
            Cursor next {cursor};

            next.col = cursor.getLineIterator()->rfind(target, cursor.getCol()-1);
            if(next.col != std::string::npos) return next;

            --next.line;
            for(auto it=cursor.getReverseLineIterator()+1; it!=cursor.getLineReverseEnd(); ++it, --next.line) {
                next.col = it->rfind(target);
                if(next.col != std::string::npos) return next;
            }

            next.line = cursor.getBufferSize()-1;
            for(auto it=cursor.getLineReverseBegin(); it!=cursor.getReverseLineIterator()+1; ++it, --next.line) {
                next.col = it->rfind(target);
                if(next.col != std::string::npos) return next;
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

