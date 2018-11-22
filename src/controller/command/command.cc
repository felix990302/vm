#include "command.h"
#include "model/file_buffer.h"


namespace VM {
    void Command::doCommand(FileBuffer &fileBuffer) {
        doTheSideEffect(fileBuffer);
        doTheCommand(fileBuffer);
    }

    void Command::doTheSideEffect(FileBuffer &filebuffer) {}

    Command::Command(const size_t &quant): quant{quant} {}

    Command::~Command() {}
}
