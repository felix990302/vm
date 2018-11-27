#ifndef ABSOLUTE_MOTION_H
#define ABSOLUTE_MOTION_H

#include "motion.h"


namespace VM {
    struct AbsoluteMotion: public ClonableMotion<Motion, AbsoluteMotion> {
        size_t linePosn;

        Cursor nextPosition(const PtrCursor &cursor) override;

        AbsoluteMotion(size_t linePosn);
    };
}

#endif
