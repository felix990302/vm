#include <cctype>
#include "model/ptr_cursor.h"
#include "first_char_motion.h"


namespace VM {
    Cursor FirstCharMotion::nextPosition(const PtrCursor &cursor) {
        Cursor position {cursor.getLine(), 0};
        const std::string &currLine = *cursor.getLineIterator();

        for(;position.col<currLine.size(); ++position.col) {
            if(!std::isspace(currLine[position.col])) return position;
        }

        return cursor;
    }

    FirstCharMotion::FirstCharMotion(size_t quant): Clonable{quant} {}
}
