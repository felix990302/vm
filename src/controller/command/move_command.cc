#include "move_command.h"
#include "motion.h"
#include "controller/controller.h"
#include "model/file_buffer.h"


namespace VM {
    void MoveCommand::doCommand(Controller &controller) { // TODO: determine interface for moving cursor
        Cursor nextCursor = controller.getBuffer().ptrCursor;
        for(size_t k=0; k<quant; ++k) {
            nextCursor = motion->nextPosition(nextCursor);
        }
    }

    std::unique_ptr<Command> MoveCommand::clone() const {
        return std::make_unique<MoveCommand>(*this);
    }

    MoveCommand::MoveCommand(size_t quant, std::unique_ptr<Motion> motion):
        Command{quant},
        motion{std::move(motion)}
    {}

    MoveCommand::MoveCommand(const MoveCommand &other):
        Command{other},
        motion{other.motion->clone()}
    {}

    MoveCommand::MoveCommand(MoveCommand &&other):
        Command{std::move(other)},
        motion{std::move(other.motion)}
    {}
}
