#ifndef COLON_COMMAND_MODE_H
#define COLON_COMMAND_MODE_H

#include <memory>
#include "controller/command/command.h"
#include "lazy_command_mode.h"


namespace VM {
    class ColonCommandMode: public LazyCommandMode {
        std::unique_ptr<Command> parseCommand(const std::string &command, const std::string &argument);
        char getStatusBarLeftIndicatorChar() override;

        public:
        void flush() override;

        ColonCommandMode(Controller &controller): LazyCommandMode{controller} {}
    };
}

#endif
