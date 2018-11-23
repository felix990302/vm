#include "command.h"
#include "model/file_buffer.h"


namespace VM {
    void Command::doCommand(Controller &controller) {
        doTheSideEffect(controller);
        doTheCommand(controller);
    }

    void Command::doTheSideEffect(Controller &controller) {}

    Command::Command(size_t quant): quant{quant} {}

    Command::~Command() {}
}
