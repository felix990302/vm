#ifndef INSERT_MODE_H
#define INSERT_MODE_H

#include "mode.h"


namespace VM {
    class InsertMode: public Mode {
        public:
        void processChar() override;
    };
}

#endif


