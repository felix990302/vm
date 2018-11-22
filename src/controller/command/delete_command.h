#ifndef DELETE_COMMAND_H
#define DELETE_COMMAND_H

#include <string>
#include "mutate_command.h"
#include "direction.h"


namespace VM {
    class DeleteCommand: public MutateCommand {
        protected:
        void doTheCommand(FileBuffer &fileBuffer) const override;
        void doTheSideEffect(FileBuffer &fileBuffer) override;
        void undoTheCommand(FileBuffer &fileBuffer) const override;

        public:
        std::unique_ptr<Command> clone() const override;
        DeleteCommand(const size_t &quant, Direction direction, const std::string &toDelete);
    };
}

#endif
