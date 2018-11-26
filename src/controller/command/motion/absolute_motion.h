#ifndef ABSOLUTE_MOTION_H
#define ABSOLUTE_MOTION_H

#include "motion.h"


namespace VM {
    struct AbsoluteMotion: public Motion {
        size_t linePosn;

        Cursor nextPosition(const PtrCursor &cursor) override;

        std::unique_ptr<Motion> clone() override;
        AbsoluteMotion(size_t linePosn);
    };
}

#endif
