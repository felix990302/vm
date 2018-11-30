#include "delete_forward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteForwardCommand::doTheCommand(Controller &controller) {
        PtrCursor &cursor = controller.getBuffer().ptrCursor;
        size_t toDelete = std::min(quant, cursor.getLineIterator()->size()-cursor.getCol());
        toMutate = cursor.getLineIterator()->substr(cursor.getCol(), toDelete);
        controller.getBuffer().delete_forward(toDelete);
    }

    void DeleteForwardCommand::undoTheCommand(Controller &controller) const {
        for(auto it=toMutate.rbegin(); it!=toMutate.rend(); ++it) {
            controller.getBuffer().type(*it);
            --controller.getBuffer().ptrCursor;
        }
    }

    void DeleteForwardCommand::redoTheCommand(Controller &controller) const {
        controller.getBuffer().delete_forward(toMutate.size());
    }

    DeleteForwardCommand::DeleteForwardCommand(DeleteForwardCommand &&other): Clonable{std::move(other)} {}

    DeleteForwardCommand::DeleteForwardCommand(size_t quant) : Clonable{quant, '\0'} {}

    DeleteForwardCommand::DeleteForwardCommand(const DeleteForwardCommand &other): Clonable{other} {}
}
