#include "join_lines.h"
#include "model/file_buffer.h"
#include "controller/controller.h"
namespace VM {

    void JoinLines::doTheCommand(Controller &controller) {
        positions.clear();
        for(size_t i = 0; i < quant; i++) {
            controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
            controller.getBuffer().ptrCursor.moveEndOfLine();
            positions.push_back(controller.getBuffer().ptrCursor);
            if (!controller.getBuffer().ptrCursor.isEOF()) {
                controller.getBuffer().delete_forward(1);
                controller.getBuffer().type(' ');
                controller.getBuffer().ptrCursor.moveLeft();
                isLineBelow = true;
            } else
            {
                isLineBelow = false;
                break;
            }
        }
    }

    void JoinLines::undoTheCommand(Controller &controller) const {
        controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
        int it = positions.size()-1;
        if(!isLineBelow) it--;
        while(it >= 0)
        {
            controller.getBuffer().ptrCursor.setCursor(positions[it]);
            controller.getBuffer().delete_forward(1);
            controller.getBuffer().type('\n');
            controller.getBuffer().ptrCursor.moveLeft();
            --it;
        }
    }

    void JoinLines::redoTheCommand(Controller &controller) const {
        for(size_t i = 0; i < quant; i++) {
            controller.getBuffer().ptrCursor.setType(PtrCursor::CursorMovement::IteratorCursor);
            controller.getBuffer().ptrCursor.moveEndOfLine();
            if (!controller.getBuffer().ptrCursor.isEOF()) {
                controller.getBuffer().delete_forward(1);
                controller.getBuffer().type(' ');
                controller.getBuffer().ptrCursor.moveLeft();
            } else
            {
                break;
            }
        }

    }
}

#include "controller/controller.h"
