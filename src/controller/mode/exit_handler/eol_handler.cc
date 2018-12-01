#include "controller/command/mutation_command.h"
#include "controller/controller.h"
#include "model/file_buffer.h"
#include "eol_handler.h"


namespace VM {
    void EOLHandler::postExit(Controller &controller, std::unique_ptr<MutationCommand> sequence) {
        PtrCursor &cursor = controller.getBuffer().ptrCursor;
        auto temp = cursor.getType();
        cursor.setType(PtrCursor::CursorMovement::IteratorCursor);

        size_t origSize = sequence->theMutateCommands.size();
        for(size_t k=1; k<quantifier; ++k) {
            for(size_t j=0; j<origSize; ++j) {
                sequence->theMutateCommands.push_back(sequence->theMutateCommands[j]->undoableclone());
                sequence->theMutateCommands.back()->doCommand(controller);
            }
        }

        cursor.setType(temp);
        controller.pushCommand(std::move(sequence));
    }
}
