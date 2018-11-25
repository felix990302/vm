#ifndef INSERT_NEWLINE_COMMAND_H
#define INSERT_NEWLINE_COMMAND_H

#include "insert_command.h"
#include "model/file_buffer.h"


namespace VM {
    class InsertNewlineCommand: public InsertCommand {
        protected:
        void doTheCommand(Controller &controller) const override;

        public:
        void undoCommand(Controller &controller) const override;

        std::unique_ptr<Command> clone() const override {
            return std::make_unique<InsertNewlineCommand>(*this);
        }
        InsertNewlineCommand(size_t quant): InsertCommand{quant, '\n'} {}
        InsertNewlineCommand(const InsertNewlineCommand &other): InsertCommand{other} {}
        InsertNewlineCommand(InsertCommand &&other): InsertCommand{std::move(other)} {}
    };
}

#endif
