#ifndef COLON_COMMAND_MODE_H
#define COLON_COMMAND_MODE_H

#include "lazy_command_mode.h"


namespace VM {
    class ColonCommandMode: public LazyCommandMode {
        std::string inputBuffer;

        ColonCommandMode(const LazyCommandMode &other) = delete; // no copies
        ColonCommandMode &operator=(const ColonCommandMode &other) = delete; // no assignment

        public:
        void flush() override;

        ColonCommandMode(Controller &controller):
            LazyCommandMode(controller),
            inputBuffer{}
        {}
    };
}

#endif
