#include "whole_line_motion.h"
#include "model/ptr_cursor.h"

namespace VM {

    Cursor WholeLineMotion::nextPosition(const PtrCursor &cursor) {
        PtrCursor p{cursor};
        p.moveDown(quantifier - 1);
        return Cursor {p.getCursor()};
    }

    WholeLineMotion::WholeLineMotion(size_t quant) : Clonable(quant) {

    }

    bool WholeLineMotion::isMultiline() const {
        return true;
    }
}