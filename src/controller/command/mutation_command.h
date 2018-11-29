#ifndef MUTATION_COMMAND_H
#define MUTATION_COMMAND_H

#include <vector>
#include "controller/mode/insert_mode_buffer_type.h"
#include "undoable_command.h"
#include "command.h"


namespace VM {
    class MutationCommand: public ClonableCommand<UndoableCommand, MutationCommand> {
        typedef std::vector<std::unique_ptr<UndoableCommand>> MutateSequence;
        MutateSequence theMutateCommands;

        public:
        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &) const override;
        void redoTheCommand(Controller &controller) const override;

        MutationCommand(size_t quant, InsertModeBufferType &&insertModeBuffer);
        MutationCommand(const MutationCommand &other);
        MutationCommand(MutationCommand &&other);
    };

}

#endif
