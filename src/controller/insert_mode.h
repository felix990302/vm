#ifndef INSERT_MODE_H
#define INSERT_MODE_H

#include "mode.h"


namespace VM {
    class InsertMode: public Mode {
        InsertMode() {} // constructor private
        InsertMode(const InsertMode &other) = delete; // no copies
        InsertMode &operator=(const InsertMode &other) = delete; // no assignment

        public:
        static InsertMode &Instance();
        void processChar(char c, Controller &controller) override;
    };
}

#endif


