#ifndef COMMAND_MODE_H
#define COMMAND_MODE_H

#include "mode.h"


namespace VM {
    class CommandMode: public Mode {
        CommandMode(const CommandMode &other) = delete; // no copies
        CommandMode &operator=(const CommandMode &other) = delete; // no assignment

        public:
        void processChar(int c) override;
        void flush() override {/*TODO: flush current command sequence*/}
        void onExit() override {flush();}

        CommandMode(Controller &controller): Mode(controller) {}
    };
}

#endif
