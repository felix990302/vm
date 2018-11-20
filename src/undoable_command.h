#ifndef UNDOABLE_COMMAND_H
#define UNDOABLE_COMMAND_H

#include "command.h"


namespace VM {
    class UndoableCommand: Command {
        public:
        virtual void UndoCommand() = 0;
        virtual void RedoCommand() = 0;
        virtual ~UndoableCommand() = 0;
    };
}

#endif
