#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include "mutate_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    template<char target> class InsertCommand: public MutateCommand {
        protected:
        void doTheCommand(Controller &controller) const override {
            controller.getBuffer()->type(toMutate); 
        }

        public:
        void undoCommand(Controller &controller) const override {
            controller.getBuffer()->delete_backward(1);
        }

        std::unique_ptr<Command> clone() const override {
            return std::make_unique<InsertCommand>(*this);
        }
        InsertCommand(size_t quant, char c): MutateCommand{quant, c} {}
        InsertCommand(const InsertCommand &other): MutateCommand{other} {}
        InsertCommand(InsertCommand &&other): MutateCommand{std::move(other)} {}
    };

    template<> class InsertCommand<'\n'>: public MutateCommand {
        protected:
        void doTheCommand(Controller &controller) const override {
            controller.getBuffer()->typeNewLine();
        }

        public:
        void undoCommand(Controller &controller) const override {
            // TODO: delete the new line char
        }

        std::unique_ptr<Command> clone() const override {
            return std::make_unique<InsertCommand>(*this);
        }
        InsertCommand(size_t quant, char c): MutateCommand{quant, c} {}
        InsertCommand(const InsertCommand &other): MutateCommand{other} {}
        InsertCommand(InsertCommand &&other): MutateCommand{std::move(other)} {}
    };
}

#endif
