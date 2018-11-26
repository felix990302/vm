#ifndef MUTATION_COMMAND_H
#define MUTATION_COMMAND_H

#include <vector>
#include "controller/mode/insert_mode_buffer_type.h"
#include "undoable_command.h"
#include "command.h"


namespace VM {
    class MutationCommand: public UndoableCommand {
        std::vector<std::unique_ptr<Command>> theMutateCommands;

        public:
        void doCommand(Controller &controller) override;
        void undoCommand(Controller &) const override {}; // TODO
        void redoCommand(Controller &controller) const override;

        std::unique_ptr<Command> clone() const override;
        MutationCommand(size_t quant, InsertModeBufferType &&insertModeBuffer);
        MutationCommand(const MutationCommand &other);
        MutationCommand(MutationCommand &&other);
    };

}

#endif
