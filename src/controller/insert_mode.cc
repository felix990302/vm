#include "model/file_buffer.h"
#include "insert_mode.h"
#include "command/insert_command.h"



namespace VM {
    void InsertMode::processChar(char c, FileBuffer &fileBuffer) {
        std::unique_ptr<Command> insert = std::make_unique<InsertCommand> (1, c);
        insert->doCommand(fileBuffer);
    }   
}
