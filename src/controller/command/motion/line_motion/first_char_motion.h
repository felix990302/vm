#ifndef FIRST_CHAR_MOTION_H
#define FIRST_CHAR_MOTION_H

#include "controller/command/motion/motion.h"


namespace VM {
    struct FirstCharMotion: public ClonableMotion<Motion, FirstCharMotion> {
        Cursor nextPosition(const PtrCursor &cursor) override;

        FirstCharMotion(size_t quant=1);
    };
}

#endif
