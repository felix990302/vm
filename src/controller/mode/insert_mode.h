#ifndef INSERT_MODE_H
#define INSERT_MODE_H

#include <deque>
#include <memory>
#include "controller/command/mutate_command/mutate_command.h"
#include "insert_mode_buffer_type.h"
#include "mode.h"


namespace VM {
   class MutateCommand; 

    class InsertMode: public Mode {
        InsertModeBufferType undoBuffer;

        InsertMode(const InsertMode &other) = delete; // no copies
        InsertMode &operator=(const InsertMode &other) = delete; // no assignment

        public:
        bool processChar(int c) override;
        void flush() override;
        void onExit() override {flush();}

        InsertMode(Controller &controller): Mode(controller) {}
    };
}

#endif
