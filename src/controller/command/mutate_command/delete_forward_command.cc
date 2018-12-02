#include "delete_forward_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void DeleteForwardCommand::doTheCommand(Controller &controller) {
        auto &cursor = controller.getBuffer().ptrCursor;
        if(cursor.isEOL()) toMutate = '\n';
        else toMutate = *cursor;
        controller.getBuffer().delete_forward(1);
    }

    void DeleteForwardCommand::undoTheCommand(Controller &controller) const {
        controller.getBuffer().type(toMutate);
        --controller.getBuffer().ptrCursor;
    }

    void DeleteForwardCommand::redoTheCommand(Controller &controller) const {
        controller.getBuffer().delete_forward(1);
    }

    DeleteForwardCommand::DeleteForwardCommand(DeleteForwardCommand &&other): Clonable{std::move(other)} {}

    DeleteForwardCommand::DeleteForwardCommand(size_t quant) : Clonable{quant, '\0'} {}

    DeleteForwardCommand::DeleteForwardCommand(const DeleteForwardCommand &other): Clonable{other} {}
}
