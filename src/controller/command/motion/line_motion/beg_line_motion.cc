#include "model/ptr_cursor.h"
#include "beg_line_motion.h"


namespace VM {
    Cursor BegLineMotion::nextPosition(const PtrCursor &cursor) {
        return Cursor{cursor.getLine(), 0}; 
    }

    BegLineMotion::BegLineMotion(size_t quant): Clonable{quant} {}
}
