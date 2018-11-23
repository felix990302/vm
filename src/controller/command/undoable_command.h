#ifndef UNDOABLE_COMMAND_H
#define UNDOABLE_COMMAND_H

#include "command.h"
#include "model/cursor.h"


namespace VM {
    class UndoableCommand: public Command {
        Cursor cursor;

        protected:
        virtual void undoTheCommand(Controller &controller) const = 0;

        public:
        const Cursor &getCursor();
        void setCursor(const Cursor &newCursor);
        void undoCommand(Controller &fileBuffer);
        virtual void redoCommand(Controller &fileBuffer);

        UndoableCommand(size_t quant);
        UndoableCommand(const UndoableCommand &other);
        UndoableCommand(UndoableCommand &&other);
        virtual ~UndoableCommand() = 0;
    };
}

#endif
