#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include "mutate_command.h"


namespace VM {
    class InsertCommand: public MutateCommand {
        protected:
        void doTheCommand(FileBuffer &fileBuffer) const override;
        void doTheSideEffect(FileBuffer &fileBuffer) override;
        void undoTheCommand(FileBuffer &fileBuffer) const override;

        public:
        std::unique_ptr<Command> clone() const override;
        InsertCommand(const size_t &quant, const std::string &toInsert);
        InsertCommand(const InsertCommand &other);
        InsertCommand(InsertCommand &&other);
    };
}

#endif
