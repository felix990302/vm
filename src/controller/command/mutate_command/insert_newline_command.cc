#include "insert_newline_command.h"
#include "controller/controller.h"


namespace VM {
    void InsertNewlineCommand::doTheCommand(Controller &controller) const {
        controller.getBuffer()->typeNewLine();
    }

    void InsertNewlineCommand::undoCommand(Controller &controller) const {
        // TODO: delete the new line char
    }
}
