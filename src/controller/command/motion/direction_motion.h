#ifndef DIRECTION_MOTION_H
#define DIRECTION_MOTION_H

#include "model/ptr_cursor.h"
#include "direction.h"
#include "motion.h"


namespace VM {
    template<Direction dir> struct DirectionMotion;

    template<> struct DirectionMotion<Direction::RIGHT>: public Motion { // default to RIGHT
        Cursor nextPosition(const PtrCursor &cursor) override {
            PtrCursor cur {cursor};
            cur.moveRight();
            return  cur;
        }
        std::unique_ptr<Motion> clone() override {
            return std::make_unique<DirectionMotion>(*this);
        }
        DirectionMotion(int quantifier = 1) : Motion(quantifier) {}
    };

    template<> struct DirectionMotion<Direction::LEFT>: public Motion {
        Cursor nextPosition(const PtrCursor &cursor) override {
            PtrCursor cur {cursor};
            cur.moveLeft();
            return  cur;
        }
        std::unique_ptr<Motion> clone() override {
            return std::make_unique<DirectionMotion>(*this);
        }
        DirectionMotion(int quantifier = 1) : Motion(quantifier) {}
    };

    template<> struct DirectionMotion<Direction::UP>: public Motion {
        Cursor nextPosition(const PtrCursor &cursor) override {
            PtrCursor cur {cursor};
            cur.moveUp();
            return  cur;
        }
        std::unique_ptr<Motion> clone() override {
            return std::make_unique<DirectionMotion>(*this);
        }
        DirectionMotion(int quantifier = 1) : Motion(quantifier) {}
    };

    template<> struct DirectionMotion<Direction::DOWN>: public Motion {
        Cursor nextPosition(const PtrCursor &cursor) override {
            PtrCursor cur {cursor};
            cur.moveDown();
            return  cur;
        }
        std::unique_ptr<Motion> clone() override {
            return std::make_unique<DirectionMotion>(*this);
        }
        DirectionMotion(int quantifier = 1) : Motion(quantifier) {}
    };
}

#endif
