#ifndef UNDO_COMMAND_H
#define UNDO_COMMAND_H

#include "command.h"


namespace VM {
    class UndoCommand: public ClonableCommand<Command, UndoCommand> {
        public:
        void doCommand(Controller &controller) override;

        UndoCommand(size_t quant);
        UndoCommand(const UndoCommand &other);
        UndoCommand(UndoCommand &&other);
    };
}

#endif
