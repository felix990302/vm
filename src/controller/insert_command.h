#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include <string>
#include "mutate_command.h"
#include "direction.h"


namespace VM {
    class InsertCommand: public MutateCommand {
        protected:
        void doTheCommand(FileBuffer &fileBuffer) const override;
        void doTheSideEffect(FileBuffer &fileBuffer) override;
        void undoTheCommand(FileBuffer &fileBuffer) const override;

        public:
        std::unique_ptr<Command> clone() const override;
        InsertCommand(const size_t &quant, Direction direction, const std::string &toInsert);
    };
}

#endif
