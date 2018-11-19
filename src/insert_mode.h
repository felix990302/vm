#ifndef INSERT_MODE_H
#define INSERT_MODE_H

#include "mode.h"


namespace VM {
    class InsertMode: Mode {
        public:
        void processChar() override;
    };
}

#endif


