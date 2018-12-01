#include "model/file_buffer.h"
#include "controller/controller.h"
#include "mutation_command.h"

namespace VM {
    void MutationCommand::doTheCommand(Controller &controller) {
        PtrCursor &cursor = controller.getBuffer().ptrCursor;
        auto temp = cursor.getType();
        cursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        for(auto &mutate : theMutateCommands) {
            mutate->doCommand(controller);
        }
        size_t orig_size = theMutateCommands.size();
        for(size_t k=1; k<quant; ++k) {
            for(size_t ind=0; ind<orig_size; ++ind) {
                theMutateCommands.push_back(theMutateCommands[ind]->undoableclone());
                theMutateCommands.back()->doCommand(controller);
            }
        }
        cursor.setType(temp);
    }

    void MutationCommand::undoTheCommand(Controller &controller) const {
        PtrCursor &cursor = controller.getBuffer().ptrCursor;
        auto temp = cursor.getType();
        cursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        for(auto it=theMutateCommands.rbegin(); it!=theMutateCommands.rend(); ++it) {
            (*it)->undoCommand(controller);
        }
        cursor.setType(temp);
    }

    void MutationCommand::redoTheCommand(Controller &controller) const {
        PtrCursor &cursor = controller.getBuffer().ptrCursor;
        auto temp = cursor.getType();
        cursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        for(auto &mutate : theMutateCommands) {
            mutate->redoCommand(controller);
        }
        cursor.setType(temp);
    }

    MutationCommand::MutationCommand(size_t quant, InsertModeBufferType &&insertModeBuffer):
        Clonable{quant},
        theMutateCommands{}
    {
        for(auto &command : insertModeBuffer) {
            theMutateCommands.push_back(std::move(command));      
        }
    }

    MutationCommand::MutationCommand(const MutationCommand &other):
        Clonable{other},
        theMutateCommands{}
    {
        for(auto &mutate : other.theMutateCommands) {
            theMutateCommands.push_back(mutate->undoableclone());
        }
    }

    MutationCommand::MutationCommand(MutationCommand &&other):
        Clonable{std::move(other)},
        theMutateCommands{std::move(other.theMutateCommands)}
    {}
}
