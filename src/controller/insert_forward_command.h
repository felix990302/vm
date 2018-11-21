#ifndef INSERT_FORWARD_COMMAND_H
#define INSERT_FORWARD_COMMAND_H

#include "mutate_command.h"


namespace VM {
    class InsertForwardCommand: public MutateCommand {
        protected:
        void doTheCommand(FileBuffer &fileBuffer) const override;
        void doTheSideEffect(FileBuffer &fileBuffer) override;
        void undoTheCommand(FileBuffer &fileBuffer) const override;

        public:
        std::unique_ptr<Command> clone() const override;
        InsertForwardCommand(const size_t &quant, const std::string &toInsert);
        InsertForwardCommand(const InsertForwardCommand &other);
        InsertForwardCommand(InsertForwardCommand &&other);
    };
}

#endif
