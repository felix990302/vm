#include "model/file_buffer.h"
#include "controller/controller.h"
#include "mutation_command.h"

namespace VM {
    void MutationCommand::doCommand(Controller &controller) {
        UndoableCommand::startPosn = controller.getBuffer().ptrCursor;
        for(auto &mutate : theMutateCommands) {
            mutate->doCommand(controller);
        }
        UndoableCommand::endPosn = controller.getBuffer().ptrCursor;
    }

    void MutationCommand::redoCommand(Controller &controller) const {
        for(auto &mutate : theMutateCommands) {
            mutate->redoCommand(controller); // FIXME: should be redo
        }
    }

    MutationCommand::MutationCommand(size_t quant, InsertModeBufferType &&insertModeBuffer):
        Clonable{quant},
        theMutateCommands{}
    {
        for(auto &command : insertModeBuffer) {
            theMutateCommands.emplace_back(std::move(command));      
        }
    }

    MutationCommand::MutationCommand(const MutationCommand &other):
        Clonable{other},
        theMutateCommands{}
    {
        for(auto &mutate : other.theMutateCommands) {
            theMutateCommands.emplace_back(mutate->undoableclone());
        }
    }

    MutationCommand::MutationCommand(MutationCommand &&other):
        Clonable{std::move(other)},
        theMutateCommands{std::move(other.theMutateCommands)}
    {}
}
