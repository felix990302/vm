#ifndef REPLACE_COMMAND_H
#define REPLACE_COMMAND_H

#include "mutate_command.h"


namespace VM {
    class ReplaceCommand: public ClonableCommand<MutateCommand, ReplaceCommand> {
        char deleted;

        void commandHelper(Controller &controller) const;
        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &controller) const override;
        void redoTheCommand(Controller &controller) const override;

        public:

        ReplaceCommand(char c): Clonable{static_cast<size_t>(1), c}, deleted{0} {}
        ReplaceCommand(const ReplaceCommand &other): Clonable{other} {}
        ReplaceCommand(ReplaceCommand &&other): Clonable{std::move(other)} {}
    };
}

#endif
