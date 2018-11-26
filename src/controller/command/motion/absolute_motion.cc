#include "model/cursor.h"
#include "absolute_motion.h"


namespace VM {
    Cursor AbsoluteMotion::nextPosition(const PtrCursor &) {
        return Cursor {linePosn, 0};
    }

    std::unique_ptr<Motion> AbsoluteMotion::clone() {
        return std::make_unique<AbsoluteMotion>(*this);
    }

    AbsoluteMotion::AbsoluteMotion(size_t linePosn):
        linePosn{linePosn}
    {}
}
