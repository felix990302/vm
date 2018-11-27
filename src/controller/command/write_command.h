#ifndef WRITE_COMMAND_H
#define WRITE_COMMAND_H

#include <string>
#include "command.h"


namespace VM {
    class WriteCommand: public Command {
        bool shouldQuit;
        std::string fileNameToWriteTo;

        void doCommand(Controller &controller) override;

        public:
        std::unique_ptr<Command> clone() const override;

        WriteCommand(bool b);
        WriteCommand(bool b, const std::string &fileNameToWriteTo);
    };
}

#endif
