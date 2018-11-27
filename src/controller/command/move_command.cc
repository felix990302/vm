#include "move_command.h"
#include "motion/motion.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void MoveCommand::doCommand(Controller &controller) { // TODO: determine interface for moving cursor
        PtrCursor &currentPtrCursor = controller.getBuffer().ptrCursor;
        for(size_t k=0; k<quant; ++k) {
            currentPtrCursor.setCursor(motion->startPosition(currentPtrCursor));
            currentPtrCursor.setCursor(motion->nextPosition(currentPtrCursor));
        }
    }

    MoveCommand::MoveCommand(size_t quant, std::unique_ptr<Motion> motion):
        ClonableCommand{quant},
        motion{std::move(motion)}
    {}

    MoveCommand::MoveCommand(const MoveCommand &other):
        ClonableCommand{other},
        motion{other.motion->clone()}
    {}

    MoveCommand::MoveCommand(MoveCommand &&other):
        ClonableCommand{std::move(other)},
        motion{std::move(other.motion)}
    {}
}
