#ifndef ESCAPE_COMMAND_H
#define ESCAPE_COMMAND_H

#include "controller/command/command.h"


namespace VM {
    class EscapeCommand: public ClonableCommand<Command, EscapeCommand> {
        public:
        void doCommand(Controller &controller) override;
    };
}

#endif
