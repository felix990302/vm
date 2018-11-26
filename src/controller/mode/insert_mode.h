#ifndef INSERT_MODE_H
#define INSERT_MODE_H

#include "insert_mode_buffer_type.h"
#include "mode.h"


namespace VM {
    class InsertMode: public Mode {
        InsertModeBufferType undoBuffer;

        InsertMode(const InsertMode &other) = delete; // no copies
        InsertMode &operator=(const InsertMode &other) = delete; // no assignment

        public:
        void processChar(int c) override;
        void flush() override;
        void onExit() override {flush();}

        InsertMode(Controller &controller): Mode(controller) {}
    };
}

#endif
