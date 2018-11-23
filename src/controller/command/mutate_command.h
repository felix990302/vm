#ifndef MUTATE_COMMAND_H
#define MUTATE_COMMAND_H

#include <string>
#include "model/cursor.h"
#include "undoable_command.h"


namespace VM {
    class MutateCommand: public UndoableCommand {
        virtual void doTheCommand(Controller &controller) const = 0;
        
        protected:
        std::string toMutate;

        public:
        void doCommand(Controller &controller) override;
        void redoCommand(Controller &controller) const override;

        MutateCommand(size_t quant, const std::string &toMutate);
        MutateCommand(size_t quant, char c);
        MutateCommand(const MutateCommand &other);
        MutateCommand(MutateCommand &&other);
        virtual ~MutateCommand();
    };
}

#endif
