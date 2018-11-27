#include "controller/controller.h"
#include "model/file_buffer.h"
#include "write_command.h"


namespace VM {
    void WriteCommand::doCommand(Controller &controller) {
        if(fileNameToWriteTo.empty()) {
            controller.getBuffer().write();
        }
        else {
            controller.getBuffer().write(fileNameToWriteTo);
        }

        if(shouldQuit) controller.quit(false);
    }

    std::unique_ptr<Command> WriteCommand::clone() const {
        return std::make_unique<WriteCommand>(*this);
    }

    WriteCommand::WriteCommand(bool b):
        shouldQuit{b},
        fileNameToWriteTo{}
    {}

    WriteCommand::WriteCommand(bool b, const std::string &fileNameToWriteTo):
        shouldQuit{b},
        fileNameToWriteTo{fileNameToWriteTo}
    {}
}
