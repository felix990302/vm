#ifndef SETLINESCOMMAND_H
#define SETLINESCOMMAND_H
#include "command.h"

namespace VM {

    class SetLinesCommand : public ClonableCommand<Command, SetLinesCommand> {
        bool onOrOff;
        void doCommand(Controller &controller) override;

    public:
        SetLinesCommand(bool on): onOrOff{on} {}

    };

}


#endif
