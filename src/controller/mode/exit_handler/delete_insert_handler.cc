#include "controller/command/mutate_command/open_line_command.h"
#include "controller/command/mutation_command.h"
#include "delete_insert_handler.h"


namespace VM {
    void DeleteInsertHandler::postExit(Controller &controller, std::unique_ptr<MutationCommand> sequence) {
        controller.pushCommand(std::move(sequence));
    }
}
