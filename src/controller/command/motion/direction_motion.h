#ifndef DIRECTION_MOTION_H
#define DIRECTION_MOTION_H

#include "model/ptr_cursor.h"
#include "direction.h"
#include "motion.h"


namespace VM {
    template<Direction dir> struct DirectionMotion;

    template<> struct DirectionMotion<Direction::RIGHT>: public ClonableMotion<Motion, DirectionMotion<Direction::RIGHT>> {
        Cursor nextPosition(const PtrCursor &cursor) override {
            PtrCursor cur {cursor};
            for(size_t k=0; k<quantifier; ++k)
                cur.moveRight();
            return  cur;
        }
        DirectionMotion(size_t quantifier = 1) : Clonable(quantifier) {}
    };

    template<> struct DirectionMotion<Direction::LEFT>: public ClonableMotion<Motion, DirectionMotion<Direction::LEFT>> {
        Cursor nextPosition(const PtrCursor &cursor) override {
            PtrCursor cur {cursor};
            for(size_t k=0; k<quantifier; ++k)
                cur.moveLeft();
            return  cur;
        }
        DirectionMotion(size_t quantifier = 1) : Clonable(quantifier) {}
    };

    template<> struct DirectionMotion<Direction::UP>: public ClonableMotion<Motion, DirectionMotion<Direction::UP>> {
        Cursor nextPosition(const PtrCursor &cursor) override {
            PtrCursor cur {cursor};
            for(size_t k=0; k<quantifier; ++k)
                cur.moveUp();
            return  cur;
        }
        DirectionMotion(size_t quantifier = 1) : Clonable(quantifier) {}
    };

    template<> struct DirectionMotion<Direction::DOWN>: public ClonableMotion<Motion, DirectionMotion<Direction::DOWN>> {
        Cursor nextPosition(const PtrCursor &cursor) override {
            PtrCursor cur {cursor};
            for(size_t k=0; k<quantifier; ++k)
                cur.moveDown();
            return  cur;
        }
        DirectionMotion(size_t quantifier = 1) : Clonable(quantifier) {}
    };
}

#endif
