#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include "mutate_command.h"
#include "model/file_buffer.h"


namespace VM {
    class InsertCommand: public ClonableCommand<MutateCommand, InsertCommand> {
        void commandHelper(Controller &controller) const;
        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &controller) const override;
        void redoTheCommand(Controller &controller) const override;

        public:

        InsertCommand(char c): Clonable{static_cast<size_t>(1), c} {}
        InsertCommand(const InsertCommand &other): Clonable{other} {}
        InsertCommand(InsertCommand &&other): Clonable{std::move(other)} {}
    };
}

#endif
