#ifndef INSERT_BACKWARD_COMMAND_H
#define INSERT_BACKWARD_COMMAND_H

#include "mutate_command.h"


namespace VM {
    class InsertBackwardCommand: public MutateCommand {
        protected:
        void doTheCommand(FileBuffer &fileBuffer) const override;
        void doTheSideEffect(FileBuffer &fileBuffer) override;
        void undoTheCommand(FileBuffer &fileBuffer) const override;

        public:
        std::unique_ptr<Command> clone() const override;
        InsertBackwardCommand(const size_t &quant, const std::string &toInsert);
        InsertBackwardCommand(const InsertBackwardCommand &other);
        InsertBackwardCommand(InsertBackwardCommand &&other);
    };
}

#endif
