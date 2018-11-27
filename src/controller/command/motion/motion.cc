#include "model/ptr_cursor.h"
#include "motion.h"


namespace VM {
    inline Cursor Motion::startPosition(const PtrCursor &cursor) {return cursor;}
    Motion::Motion(size_t quantifier) : quantifier (quantifier) {}
    Motion::Motion() : quantifier(1) {}

    Motion::~Motion() {}
}
