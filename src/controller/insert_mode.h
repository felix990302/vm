#ifndef INSERT_MODE_H
#define INSERT_MODE_H

#include "mode.h"


namespace VM {
    class InsertMode: public Mode {
        InsertMode(const InsertMode &other) = delete; // no copies
        InsertMode &operator=(const InsertMode &other) = delete; // no assignment

        public:
        bool processChar(int c) override;
        void flush() override {/*TODO: flush queue and make sequence of commands*/}
        void onExit() override {flush();}

        InsertMode(Controller &controller): Mode(controller) {}
    };
}

#endif


