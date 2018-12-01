#ifndef WholeLineMotion_H
#define WholeLineMotion_H
#include "controller/command/motion/motion.h"



namespace VM {

    class WholeLineMotion : public ClonableMotion<Motion, WholeLineMotion> {
        Cursor nextPosition(const PtrCursor &cursor) override;



    public:
        bool isMultiline() const override;
        WholeLineMotion(size_t quant = 1);
    };

}


#endif
