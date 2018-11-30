#include "model/ptr_cursor.h"
#include "eol_motion.h"


namespace VM {
    Cursor EOLMotion::nextPosition(const PtrCursor &cursor) {
        return Cursor{cursor.getLine(), cursor.getLineIterator()->size()-1};
    }

    EOLMotion::EOLMotion(size_t quant): Clonable{quant} {}
}
