#ifndef UNDOABLE_COMMAND_H
#define UNDOABLE_COMMAND_H

#include "command.h"


namespace VM {
    class UndoableCommand: public Command {
        protected:
        virtual void undoTheCommand() = 0;

        public:
        void undoCommand();
        virtual void redoCommand();

        UndoableCommand(const size_t &quant);
        virtual ~UndoableCommand() = 0;
    };
}

#endif
