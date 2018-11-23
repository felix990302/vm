#ifndef UNDOABLE_COMMAND_H
#define UNDOABLE_COMMAND_H

#include "command.h"
#include "model/cursor.h"


namespace VM {
    class UndoableCommand: public Command {
        protected:
        Cursor startPosn, endPosn;


        public:
        virtual void undoCommand(Controller &fileBuffer) const = 0;
        virtual void redoCommand(Controller &fileBuffer) const = 0;

        UndoableCommand(size_t quant);
        UndoableCommand(const UndoableCommand &other);
        UndoableCommand(UndoableCommand &&other);
        virtual ~UndoableCommand() = 0;
    };
}

#endif
