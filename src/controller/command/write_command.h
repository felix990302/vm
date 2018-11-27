#ifndef WRITE_COMMAND_H
#define WRITE_COMMAND_H

#include <string>
#include "command.h"


namespace VM {
    class WriteCommand: public ClonableCommand<Command, WriteCommand> {
        bool shouldQuit;
        std::string fileNameToWriteTo;

        public:
        void doCommand(Controller &controller) override;
        WriteCommand(bool b);
        WriteCommand(bool b, const std::string &fileNameToWriteTo);
    };
}

#endif
