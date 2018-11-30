#ifndef EOL_MOTION_H
#define EOL_MOTION_H

#include "motion.h"


namespace VM {
    struct EOLMotion: public ClonableMotion<Motion, EOLMotion> {
        Cursor nextPosition(const PtrCursor &cursor) override;

        EOLMotion(size_t=1);
    };
}

#endif
