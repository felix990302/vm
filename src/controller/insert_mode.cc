#include "model/file_buffer.h"
#include "insert_mode.h"
#include "command/insert_command.h"



namespace VM {
    InsertMode &InsertMode::Instance() {
        static InsertMode singleton;

        return singleton;
    }

    void InsertMode::processChar(char c, Controller &controller) {
        std::unique_ptr<Command> insert = std::make_unique<InsertCommand> (1, c);
        insert->doCommand(controller);
    }   
}
