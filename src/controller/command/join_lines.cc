#include "join_lines.h"
#include "model/file_buffer.h"
#include "controller/controller.h"

namespace VM {

    void JoinLines::doTheCommand(Controller &controller) {
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        controller.getBuffer().ptrCursor.moveEndOfLine();
        if(!controller.getBuffer().ptrCursor.isEOF()) {
            controller.getBuffer().delete_forward(1);
            controller.getBuffer().type(' ');
            controller.getBuffer().ptrCursor.moveLeft();
            isLineBelow=true;
        } else isLineBelow = false;
    }

    void JoinLines::undoTheCommand(Controller &controller) const {
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        if(isLineBelow)
        {
            controller.getBuffer().delete_forward(1);
            controller.getBuffer().type('\n');
        }

    }

    void JoinLines::redoTheCommand(Controller &controller) const {
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        controller.getBuffer().ptrCursor.moveEndOfLine();
        if(isLineBelow)
        {
            controller.getBuffer().delete_forward(1);
            controller.getBuffer().type(' ');
            controller.getBuffer().ptrCursor.moveLeft();
        }

    }
}