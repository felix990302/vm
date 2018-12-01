#include "delete_backward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteBackwardCommand::doTheCommand(Controller &controller) {
        //PtrCursor &cursor = controller.getBuffer().ptrCursor;
        size_t toDelete = quant;// std::min(quant, cursor.getCol());
        //toMutate = cursor.getLineIterator()->substr(cursor.getCol()-toDelete, toDelete);
        controller.getBuffer().delete_backward(toDelete);
    }

    void DeleteBackwardCommand::undoTheCommand(Controller &controller) const {
        for(auto c : toMutate)
            controller.getBuffer().type(c);
    }

    void DeleteBackwardCommand::redoTheCommand(Controller &controller) const {
        controller.getBuffer().delete_backward(toMutate.size());
    }

    DeleteBackwardCommand::DeleteBackwardCommand(const DeleteBackwardCommand &other): Clonable{other} {}

    DeleteBackwardCommand::DeleteBackwardCommand(size_t quant): Clonable{quant, '\0'} {}

    DeleteBackwardCommand::DeleteBackwardCommand(DeleteBackwardCommand &&other): Clonable{std::move(other)} {}
}
