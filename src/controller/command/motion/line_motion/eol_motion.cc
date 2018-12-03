#include "model/ptr_cursor.h"
#include "eol_motion.h"


namespace VM {
    Cursor EOLMotion::nextPosition(const PtrCursor &cursor) {
        PtrCursor cur {cursor};
        cur.setType(PtrCursor::CursorMovement::IteratorCursor);
        cur.moveEndOfLine();
        return cur;
    }

    EOLMotion::EOLMotion(size_t quant): Clonable{quant} {}
}
