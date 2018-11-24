#ifndef INSERT_MODE_H
#define INSERT_MODE_H

#include "mode.h"


namespace VM {
    class InsertMode: public Mode {
        InsertMode(const InsertMode &other) = delete; // no copies
        InsertMode &operator=(const InsertMode &other) = delete; // no assignment

        public:
        void processChar(char c) override;

        InsertMode(Controller &controller): Mode(controller) {}
    };
}

#endif


