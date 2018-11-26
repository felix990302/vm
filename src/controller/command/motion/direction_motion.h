#ifndef DIRECTION_MOTION_H
#define DIRECTION_MOTION_H

#include "model/ptr_cursor.h"
#include "direction.h"
#include "motion.h"


namespace VM {
    template<Direction dir> struct DirectionMotion;

    template<> struct DirectionMotion<Direction::RIGHT>: public Motion { // default to RIGHT
        Cursor nextPosition(const PtrCursor &cursor) override {
            return Cursor{cursor.line, cursor.col+1}; 
        }
        std::unique_ptr<Motion> clone() override {
            return std::make_unique<DirectionMotion>(*this);
        }
        DirectionMotion(int quantifier = 1) : Motion(quantifier) {}
    };

    template<> struct DirectionMotion<Direction::LEFT>: public Motion {
        Cursor nextPosition(const PtrCursor &cursor) override {
            return Cursor{cursor.line, cursor.col ? cursor.col-1 : cursor.col};
        }
        std::unique_ptr<Motion> clone() override {
            return std::make_unique<DirectionMotion>(*this);
        }
        DirectionMotion(int quantifier = 1) : Motion(quantifier) {}
    };

    template<> struct DirectionMotion<Direction::UP>: public Motion {
        Cursor nextPosition(const PtrCursor &cursor) override {
            return Cursor{cursor.line ? cursor.line-1 : cursor.line, cursor.col};
        }
        std::unique_ptr<Motion> clone() override {
            return std::make_unique<DirectionMotion>(*this);
        }
        DirectionMotion(int quantifier = 1) : Motion(quantifier) {}
    };

    template<> struct DirectionMotion<Direction::DOWN>: public Motion {
        Cursor nextPosition(const PtrCursor &cursor) override {
            return Cursor{cursor.line+1, cursor.col}; 
        }
        std::unique_ptr<Motion> clone() override {
            return std::make_unique<DirectionMotion>(*this);
        }
        DirectionMotion(int quantifier = 1) : Motion(quantifier) {}
    };
}

#endif
