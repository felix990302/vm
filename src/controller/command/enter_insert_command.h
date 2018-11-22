#ifndef ENTER_INSERT_COMMAND_H
#define ENTER_INSERT_COMMAND_H

#include "command.h"


namespace VM {
    class EnterInsertCommand: public Command {
        protected:
        void doTheCommand(FileBuffer &filebuffer) const override;

        public:
        EnterInsertCommand();
        std::unique_ptr<Command> clone() const override;
    };
}

#endif
