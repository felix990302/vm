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
    }

    std::unique_ptr<Command> WriteCommand::clone() const {
        return std::make_unique<WriteCommand>(*this);
    }

    WriteCommand::WriteCommand():
        fileNameToWriteTo{}
    {}

    WriteCommand::WriteCommand(const std::string &fileNameToWriteTo):
        fileNameToWriteTo{fileNameToWriteTo}
    {}
}
