#ifndef REPLACE_CHAR_COMMAND_H
#define REPLACE_CHAR_COMMAND_H

#include "undoable_command.h"
#include "model/file_buffer.h"


namespace VM {
    class ReplaceCharCommand: public ClonableCommand<UndoableCommand, ReplaceCharCommand> {
        void commandHelper(Controller &controller) const;
        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &controller) const override;
        void redoTheCommand(Controller &controller) const override;

        protected:
        char inserted;
        char deleted;

        public:
        ReplaceCharCommand(char c): Clonable{static_cast<size_t>(1)}, inserted{c} {}
        ReplaceCharCommand(const ReplaceCharCommand &other): Clonable{other}, deleted{other.deleted} {}
        ReplaceCharCommand(ReplaceCharCommand &&other): Clonable{std::move(other)}, deleted{std::move(other.deleted)} {}
    };
}

#endif
