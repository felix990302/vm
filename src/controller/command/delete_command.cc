#include "delete_command.h"
#include "model/ptr_cursor.h"
#include "model/file_buffer.h"
#include "controller/controller.h"

namespace VM {


    void DeleteCommand::doTheCommand(Controller &controller) {
        PtrCursor begin {controller.getBuffer().ptrCursor};
        motion->quantifier *= quant;
        quant = 1;
        PtrCursor end {motion->nextPosition(begin), controller.getBuffer().getBuffer(), PtrCursor::CursorMovement::IteratorCursor};
        begin.setType(PtrCursor::CursorMovement::IteratorCursor);

        if(end < begin) std::swap(begin,end);
        beginPosition = begin.getCursor();
        isMultiline = motion->isMultiline();
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        if(isMultiline)
        {
            beginPosition.col = 0;
            for(auto it = begin.getLineIterator(); it <= end.getLineIterator(); ++it)
                buffer += *it + "\n";
            controller.getBuffer().ptrCursor.setCursor(beginPosition);

        }
        else
        {
            int toDelete = end - begin;
            controller.getBuffer().ptrCursor.setCursor(beginPosition);
            buffer = controller.getBuffer().getSubBuffer(toDelete);

        }
        controller.getBuffer().delete_forward(buffer.size());
    }

    void DeleteCommand::undoTheCommand(Controller &controller) const {
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        controller.getBuffer().type(buffer);
        if(controller.getBuffer().ptrCursor.isEOF()) controller.getBuffer().delete_backward(1);
    }

    void DeleteCommand::redoTheCommand(Controller &controller) const {
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        controller.getBuffer().ptrCursor.setCursor(beginPosition);
        controller.getBuffer().delete_forward(buffer.size());
    }

    DeleteCommand::DeleteCommand(size_t quant, std::unique_ptr<Motion> motion) : Clonable {quant}, beginPosition {0,0} , motion {std::move(motion)} {
    }

    DeleteCommand::DeleteCommand(const DeleteCommand &other) : Clonable {other.quant}, beginPosition{other.beginPosition}, motion{motion->clone()}  {

    }

    DeleteCommand::DeleteCommand(DeleteCommand &&other) : Clonable {other.quant}, beginPosition{other.beginPosition}, motion{std::move(other.motion)} {

    }
}
