#include "yank_command.h"

namespace VM {

    void YankCommand::doCommand(Controller &controller) {
        LineType buffer;
        bool isMultiline;
        PtrCursor begin {controller.getBuffer().ptrCursor};
        motion->quantifier *= quant;
        quant = 1;
        begin.setType(PtrCursor::CursorMovement::InsertModeCursor);
        PtrCursor end {motion->nextPosition(begin), controller.getBuffer().getBuffer(), PtrCursor::CursorMovement::IteratorCursor};
        begin.setType(PtrCursor::CursorMovement::IteratorCursor);

        if(end < begin) std::swap(begin,end);
        Cursor beginPosition {begin.getCursor()};
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
            int toCopy = end - begin;
            controller.getBuffer().ptrCursor.setCursor(beginPosition);
            buffer = controller.getBuffer().getSubBuffer(toCopy);
        }
        controller.clipBoard.multiLine = isMultiline;
        controller.clipBoard.theClipBoard = buffer;
    }

    YankCommand::YankCommand(size_t quant, std::unique_ptr<Motion> motion) : Clonable {quant}, motion {std::move(motion)} {

    }

    YankCommand::YankCommand(const YankCommand &other)  : Clonable {other.quant}, motion{other.motion->clone()}   {

    }

    YankCommand::YankCommand(YankCommand &&other)  : Clonable {other.quant}, motion{std::move(other.motion)} {

    }


}
