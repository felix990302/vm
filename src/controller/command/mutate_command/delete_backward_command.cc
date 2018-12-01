#include "delete_backward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteBackwardCommand::doTheCommand(Controller &controller) {
        const PtrCursor &cursor = controller.getBuffer().ptrCursor;
        if(cursor.getCol() == 0) toMutate = '\n';
        else toMutate = *(cursor.getStringIterator()-1);
        controller.getBuffer().delete_backward(1);
    }

    void DeleteBackwardCommand::undoTheCommand(Controller &controller) const {
        controller.getBuffer().type(toMutate);
    }

    void DeleteBackwardCommand::redoTheCommand(Controller &controller) const {
        auto temp = controller.getBuffer().ptrCursor.getType();
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        controller.getBuffer().delete_backward(1);
        controller.getBuffer().ptrCursor.setType(temp);
    }

    DeleteBackwardCommand::DeleteBackwardCommand(const DeleteBackwardCommand &other): Clonable{other} {}

    DeleteBackwardCommand::DeleteBackwardCommand(size_t quant): Clonable{quant, '\0'} {}

    DeleteBackwardCommand::DeleteBackwardCommand(DeleteBackwardCommand &&other): Clonable{std::move(other)} {}
}
