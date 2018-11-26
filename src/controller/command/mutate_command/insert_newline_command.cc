#include "insert_newline_command.h"
#include "controller/controller.h"


namespace VM {
    void InsertNewlineCommand::doTheCommand(Controller &controller) const {
        for(size_t k=0; k<quant; ++k) controller.getBuffer().typeNewLine();
    }

    void InsertNewlineCommand::undoCommand(Controller &) const {} // TODO
}
