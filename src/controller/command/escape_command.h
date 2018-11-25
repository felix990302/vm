#ifndef ESCAPE_COMMAND_H
#define ESCAPE_COMMAND_H

#include "command.h"


namespace VM {
    class EscapeCommand: public Command {
        void doCommand(Controller &controller) override;

        public:
        std::unique_ptr<Command> clone() const override;
    };
}

#endif
