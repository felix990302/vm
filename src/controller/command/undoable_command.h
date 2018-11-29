#ifndef UNDOABLE_COMMAND_H
#define UNDOABLE_COMMAND_H

#include "command.h"
#include "model/cursor.h"


namespace VM {
    class UndoableCommand: public Command {
        virtual void doTheCommand(Controller &) = 0;
        virtual void undoTheCommand(Controller &) const = 0;
        virtual void redoTheCommand(Controller &) const = 0;

        protected:
        Cursor startPosn, endPosn;

        public:
        void doCommand(Controller &) override final;
        void undoCommand(Controller &) const;
        void redoCommand(Controller &) const;

        std::unique_ptr<UndoableCommand> undoableclone() const;
        UndoableCommand(size_t quant, Cursor startPosn=Cursor{0, 0}, Cursor endPosn=Cursor{0, 0});
        UndoableCommand(const UndoableCommand &other);
        UndoableCommand(UndoableCommand &&other);
        virtual ~UndoableCommand() = 0;
    };
}

#endif
