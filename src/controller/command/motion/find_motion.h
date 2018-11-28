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
            PtrCursor cur {cursor};
            cur.setType(PtrCursor::CursorMovement::InsertModeCursor);

            int q = 0;
            do {
                cur.moveRight();
                if(*cur) ++q;
            } while (q !=quantifier && !cur.isEOL());

            if(q!=quantifier)
                return cursor;
            return cur;
        }

        FindMotion(size_t quantifier, char c): Clonable{quantifier}, target{c} {}
    };

    template<> struct FindMotion<Direction::LEFT>: public ClonableMotion<Motion, FindMotion<Direction::LEFT>> {
        char target;

        Cursor nextPosition(const PtrCursor &cursor) override {
            PtrCursor cur {cursor};
            cur.setType(PtrCursor::CursorMovement::InsertModeCursor);

            int q = 0;
            do {
                cur.moveLeft();
                if(*cur) ++q;
            } while (q !=quantifier && cur.getCol() != 0);

            if(q!=quantifier)
                return cursor;
            return cur;
        }

        FindMotion(size_t quantifier, char c): Clonable{quantifier}, target{c} {}
    };
}

#endif
