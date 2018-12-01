#ifndef MATCH_BRACE_MOTION
#define MATCH_BRACE_MOTION

#include "motion.h"


namespace VM {
   struct MatchBraceMotion: public ClonableMotion<Motion, MatchBraceMotion> {
        Cursor nextPosition(const PtrCursor &other) override;

        MatchBraceMotion(size_t quant=1): Clonable{quant} {}
   };
}

#endif
