#include "delete_forward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteForwardCommand::doTheCommand(Controller &controller) {
        //PtrCursor &cursor = controller.getBuffer().ptrCursor;
        //if(cursor.getStringIterator() == cursor.getLineIterator()->end()) toMutate = '\n';
        //else toMutate = *(cursor.getStringIterator());
        controller.getBuffer().delete_forward(1);
    }

    void DeleteForwardCommand::undoTheCommand(Controller &controller) const {
        controller.getBuffer().type(toMutate);
        //--controller.getBuffer().ptrCursor;
    }

    void DeleteForwardCommand::redoTheCommand(Controller &controller) const {
        //auto temp = controller.getBuffer().ptrCursor.getType();
        //controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        controller.getBuffer().delete_forward(1);
        //controller.getBuffer().ptrCursor.setType(temp);
    }

    DeleteForwardCommand::DeleteForwardCommand(DeleteForwardCommand &&other): Clonable{std::move(other)} {}

    DeleteForwardCommand::DeleteForwardCommand(size_t quant) : Clonable{quant, '\0'} {}

    DeleteForwardCommand::DeleteForwardCommand(const DeleteForwardCommand &other): Clonable{other} {}
}
