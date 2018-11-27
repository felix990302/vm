#include "model/cursor.h"
#include "absolute_motion.h"


namespace VM {
    Cursor AbsoluteMotion::nextPosition(const PtrCursor &) {
        return Cursor {linePosn, 0};
    }

    AbsoluteMotion::AbsoluteMotion(size_t linePosn):
        linePosn{linePosn}
    {}
}
