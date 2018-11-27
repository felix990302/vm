#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include "mutate_command.h"
#include "model/file_buffer.h"


namespace VM {
    class InsertCommand: public ClonableCommand<MutateCommand, InsertCommand> {
        protected:
        void doTheCommand(Controller &controller) const override;

        public:
        void undoCommand(Controller &controller) const override;

        InsertCommand(size_t quant, char c): ClonableCommand{quant, c} {}
        InsertCommand(const InsertCommand &other): ClonableCommand{other} {}
        InsertCommand(InsertCommand &&other): ClonableCommand{std::move(other)} {}
    };
}

#endif
