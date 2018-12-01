#ifndef REPLACE_COMMAND_H
#define REPLACE_COMMAND_H

#include "mutate_command.h"
#include "model/file_buffer.h"


namespace VM {
    class ReplaceCommand: public ClonableCommand<MutateCommand, ReplaceCommand> {
        void commandHelper(Controller &controller) const;
        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &controller) const override;
        void redoTheCommand(Controller &controller) const override;

        protected:
        char deleted;

        public:
        ReplaceCommand(char c): Clonable{static_cast<size_t>(1), c} {}
        ReplaceCommand(const ReplaceCommand &other): Clonable{other}, deleted{other.deleted} {}
        ReplaceCommand(ReplaceCommand &&other): Clonable{std::move(other)}, deleted{std::move(other.deleted)} {}
    };
}

#endif
