#ifndef UNDOABLE_COMMAND_H
#define UNDOABLE_COMMAND_H

#include "command.h"
#include "model/cursor.h"


namespace VM {
    class UndoableCommand: public Command {
        protected:
        Cursor startPosn, endPosn;

        public:
        virtual void undoCommand(Controller &) const = 0;
        virtual void redoCommand(Controller &) const = 0;

        std::unique_ptr<UndoableCommand> undoableclone() const;
        UndoableCommand(size_t quant, Cursor startPosn=Cursor{0, 0}, Cursor endPosn=Cursor{0, 0});
        UndoableCommand(const UndoableCommand &other);
        UndoableCommand(UndoableCommand &&other);
        virtual ~UndoableCommand() = 0;
    };
}

#endif
