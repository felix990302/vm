#ifndef UNDOABLE_COMMAND_H
#define UNDOABLE_COMMAND_H

#include "command.h"
#include "model/cursor.h"


namespace VM {
    class UndoableCommand: public Command {
        Cursor cursor;

        protected:
        virtual void undoTheCommand(FileBuffer &fileBuffer) const = 0;

        public:
        void undoCommand(FileBuffer &fileBuffer);
        virtual void redoCommand(FileBuffer &fileBuffer);

        UndoableCommand(const size_t &quant);
        virtual ~UndoableCommand() = 0;
    };
}

#endif
