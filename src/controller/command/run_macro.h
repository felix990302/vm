#ifndef RUNMACRO_H
#define RUNMACRO_H

#include "controller/command/undoable_command.h"

namespace VM {

    class RunMacro : public ClonableCommand <UndoableCommand, RunMacro> {
        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &controller) const override;
        void redoTheCommand(Controller &controller) const override;

    public:

        RunMacro(size_t quant, char '')
        RunMacro(const RunMacro&);
        RunMacro(RunMacro&&);
    };

}


#endif
