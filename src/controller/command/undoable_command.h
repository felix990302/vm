#ifndef UNDOABLE_COMMAND_H
#define UNDOABLE_COMMAND_H

#include "command.h"
#include "model/cursor.h"


namespace VM {
    class UndoableCommand: public Command {
        protected:
        Cursor startPosn {0, 0}, endPosn {0, 0};


        public:
        virtual void undoCommand(Controller &) const {}; // TODO
        virtual void redoCommand(Controller &) const {}; // TODO

        UndoableCommand(size_t quant);
        UndoableCommand(const UndoableCommand &other);
        UndoableCommand(UndoableCommand &&other);
        virtual ~UndoableCommand() = 0;
    };
}

#endif
