#include "model/file_buffer.h"
#include "controller/controller.h"
#include "mutation_command.h"

namespace VM {
    void MutationCommand::doTheCommand(Controller &controller) {
        for(auto &mutate : theMutateCommands) {
            mutate->doCommand(controller);
        }
    }

    void MutationCommand::undoTheCommand(Controller &controller) const {
        for(auto it=theMutateCommands.rbegin(); it!=theMutateCommands.rend(); ++it) {
            (*it)->undoCommand(controller);
        }
    }

    void MutationCommand::redoTheCommand(Controller &controller) const {
        for(auto &mutate : theMutateCommands) {
            mutate->redoCommand(controller);
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
