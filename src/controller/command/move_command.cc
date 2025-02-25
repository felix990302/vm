#include "move_command.h"
#include "motion/motion.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void MoveCommand::doCommand(Controller &controller) {
        PtrCursor &currentPtrCursor = controller.getBuffer().ptrCursor;
        for(size_t k=0; k<quant; ++k) {
            currentPtrCursor.setCursor(motion->startPosition(currentPtrCursor));
            currentPtrCursor.setCursor(motion->nextPosition(currentPtrCursor));
            currentPtrCursor.setType(PtrCursor::CursorMovement::NormalModeCursor);
        }
    }

    MoveCommand::MoveCommand(size_t quant, std::unique_ptr<Motion> motion):
        Clonable{quant},
        motion{std::move(motion)}
    {}

    MoveCommand::MoveCommand(const MoveCommand &other):
        Clonable{other},
        motion{other.motion->clone()}
    {}

    MoveCommand::MoveCommand(MoveCommand &&other):
        Clonable{std::move(other)},
        motion{std::move(other.motion)}
    {}
}
