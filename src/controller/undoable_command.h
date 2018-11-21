#ifndef UNDOABLE_COMMAND_H
#define UNDOABLE_COMMAND_H

#include "command.h"


namespace VM {
    class UndoableCommand: public Command {
        public:
        virtual void undoCommand() = 0;
        virtual void redoCommand() = 0;

        UndoableCommand(const size_t &quant);
        virtual ~UndoableCommand() = 0;
    };
}

#endif
