#include "command.h"
#include "model/file_buffer.h"


namespace VM {
    Command::Command(size_t quant): quant{quant} {}

    Command::~Command() {}
}
