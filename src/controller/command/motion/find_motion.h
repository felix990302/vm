#ifndef FIND_MOTION_H
#define FIND_MOTION_H

#include "model/ptr_cursor.h"
#include "direction.h"
#include "motion.h"


namespace VM {
    template<Direction dir> struct FindMotion;

    template<> struct FindMotion<Direction::RIGHT>: public ClonableMotion<Motion, FindMotion<Direction::RIGHT>> { 
        char target;

        Cursor nextPosition(const PtrCursor &cursor) override {
            Cursor position {cursor};
            size_t count = 0;
            
            ++position.col;
            for(auto it=cursor.getStringIterator()+1;it!=cursor.getLineIterator()->end(); ++it, ++position.col) {
                if(*it==target && ++count==quantifier) return position;
            }

            return cursor;
        }

        FindMotion(size_t quantifier, char c): Clonable{quantifier}, target{c} {}
    };

    template<> struct FindMotion<Direction::LEFT>: public ClonableMotion<Motion, FindMotion<Direction::LEFT>> {
        char target;

        Cursor nextPosition(const PtrCursor &cursor) override {
            Cursor position {cursor};
            size_t count = 0;
            
            --position.col;
            for(auto it=cursor.getReverseStringIterator()+1; it!=cursor.getReverseLineIterator()->rend(); ++it, --position.col) {
                if(*it==target && ++count==quantifier) return position;
            }

            return cursor;
        }

        FindMotion(size_t quantifier, char c): Clonable{quantifier}, target{c} {}
    };
}

#endif
