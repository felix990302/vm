#ifndef FIND_MOTION_H
#define FIND_MOTION_H

#include "model/ptr_cursor.h"
#include "direction.h"
#include "motion.h"


namespace VM {
    template<Direction dir> struct FindMotion;

    template<> struct FindMotion<Direction::RIGHT>: public Motion {
        char target;

        Cursor nextPosition(const PtrCursor &cursor) override {
            Cursor next {cursor.line, cursor.col+1};
            for(auto it=cursor.getStringIterator()+1; it!=cursor.getLineIterator()->end(); ++it, ++next.col) {
                if(*it == target) return next;
            }
            
            return cursor;
        }

        std::unique_ptr<Motion> clone() override {
            return std::make_unique<FindMotion>(*this);
        }

        FindMotion(char c): target{c} {}
    };

    template<> struct FindMotion<Direction::LEFT>: public Motion {
        char target;

        Cursor nextPosition(const PtrCursor &cursor) override {
            Cursor next {cursor.line, cursor.col-1};
            for(auto it=cursor.getReverseStringIterator()+1; it!=cursor.getLineIterator()->rend(); ++it, --next.col) {
                if(*it == target) return next;
            }
            
            return cursor;
        }

        std::unique_ptr<Motion> clone() override {
            return std::make_unique<FindMotion>(*this);
        }

        FindMotion(char c): target{c} {}
    };
}

#endif
