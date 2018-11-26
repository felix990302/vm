#include "model/ptr_cursor.h"
#include "motion.h"


namespace VM {
    inline Cursor Motion::startPosition(const PtrCursor &cursor) {return cursor;}
    Motion::Motion(int quantifier) : quantifier (quantifier) {}
    Motion::Motion() : quantifier(1) {}
}
