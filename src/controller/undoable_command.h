#ifndef UNDOABLE_COMMAND_H
#define UNDOABLE_COMMAND_H

#include "command.h"


namespace VM {
    class UndoableCommand: public Command {
        public:
        virtual void UndoCommand() = 0;
        virtual void RedoCommand() = 0;

        UndoableCommand(const size_t &quant);
        virtual ~UndoableCommand() = 0;
    };
}

#endif
