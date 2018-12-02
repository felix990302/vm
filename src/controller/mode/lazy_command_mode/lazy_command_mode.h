#ifndef LAZY_COMMAND_MODE_H
#define LAZY_COMMAND_MODE_H

#include <string>
#include "controller/mode/mode.h"


namespace VM {
    class LazyCommandMode: public Mode {
        LazyCommandMode(const LazyCommandMode &other) = delete; // no copies
        LazyCommandMode &operator=(const LazyCommandMode &other) = delete; // no assignment

        virtual char getStatusBarLeftIndicatorChar() = 0;

        protected:
        std::string commandString;

        public:
        void processChar(int c) override final;
        void onExit() override final;

        LazyCommandMode(Controller &controller):
            Mode(controller),
            commandString{}
        {}

        std::string getStatusBarLeft() override final;

        int getStatusBarCursor() override;

        virtual ~LazyCommandMode() = 0;
    };
}

#endif
