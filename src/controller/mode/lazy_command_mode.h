#ifndef LAZY_COMMAND_MODE_H
#define LAZY_COMMAND_MODE_H

#include <string>
#include "mode.h"


namespace VM {
    class LazyCommandMode: public Mode {
        std::string commandString;

        LazyCommandMode(const LazyCommandMode &other) = delete; // no copies
        LazyCommandMode &operator=(const LazyCommandMode &other) = delete; // no assignment

        public:
        void processChar(int c) override final;
        void flush() override = 0;
        void onExit() override final;

        LazyCommandMode(Controller &controller):
            Mode(controller),
            commandString{}
        {}

        virtual ~LazyCommandMode() = 0;
    };
}

#endif
