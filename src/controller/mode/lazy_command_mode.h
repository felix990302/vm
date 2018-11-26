#ifndef LAZY_COMMAND_MODE_H
#define LAZY_COMMAND_MODE_H

#include <string>
#include "mode.h"


namespace VM {
    class LazyCommandMode: public Mode {
        std::string inputBuffer;

        LazyCommandMode(const LazyCommandMode &other) = delete; // no copies
        LazyCommandMode &operator=(const LazyCommandMode &other) = delete; // no assignment

        public:
        void processChar(int c) override final; //TODO
        void flush() override {}; //TODO
        void onExit() override final {}; //TODO 

        LazyCommandMode(Controller &controller):
            Mode(controller),
            inputBuffer{}
        {}

        virtual ~LazyCommandMode() = 0;
    };
}

#endif
