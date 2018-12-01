#include "controller/command/mutate_command/open_line_command.h"
#include "controller/command/mutation_command.h"
#include "open_line_handler.h"


namespace VM {
    void OpenLineHandler::postExit(Controller &controller, std::unique_ptr<MutationCommand> sequence) {
        PtrCursor &cursor = controller.getBuffer().ptrCursor;
        auto temp = cursor.getType();
        cursor.setType(PtrCursor::CursorMovement::IteratorCursor);

        size_t origSize = sequence->theMutateCommands.size();
        for(size_t k=1; k<quantifier; ++k) {
            sequence->theMutateCommands.push_back(std::make_unique<OpenLineCommand<Direction::DOWN>>(1));
            sequence->theMutateCommands.back()->doCommand(controller);
            for(size_t j=1; j<origSize; ++j) {
                sequence->theMutateCommands.push_back(sequence->theMutateCommands[j]->undoableclone());
                sequence->theMutateCommands.back()->doCommand(controller);
            }
        }

        cursor.setType(temp);
        controller.pushCommand(std::move(sequence));
    }
}
