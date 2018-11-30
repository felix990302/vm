#ifndef BEG_LINE_MOTION_H
#define BEG_LINE_MOTION_H

#include "controller/command/motion/motion.h"


namespace VM {
    struct BegLineMotion: public ClonableMotion<Motion, BegLineMotion> {
        Cursor nextPosition(const PtrCursor &cursor) override;

        BegLineMotion(size_t quant=1);
    };
}

#endif
