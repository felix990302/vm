#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include "mutate_command.h"
#include "model/file_buffer.h"


namespace VM {
    class InsertCommand: public MutateCommand {
        protected:
        void doTheCommand(Controller &controller) const override;

        public:
        void undoCommand(Controller &controller) const override;

        std::unique_ptr<Command> clone() const override {
            return std::make_unique<InsertCommand>(*this);
        }
        InsertCommand(size_t quant, char c): MutateCommand{quant, c} {}
        InsertCommand(const InsertCommand &other): MutateCommand{other} {}
        InsertCommand(InsertCommand &&other): MutateCommand{std::move(other)} {}
    };
}

#endif
