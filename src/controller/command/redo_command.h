#ifndef REDO_COMMAND_H
#define REDO_COMMAND_H

#include "command.h"


namespace VM {
    class RedoCommand: public ClonableCommand<Command, RedoCommand> {
        public:
        void doCommand(Controller &controller) override;

        RedoCommand(size_t quant);
        RedoCommand(const RedoCommand &other);
        RedoCommand(RedoCommand &&other);
    };
}

#endif
