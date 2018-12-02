#ifndef RUN_MACRO_COMMAND_H
#define RUN_MACRO_COMMAND_H

#include <vector>
#include "controller/command/undoable_command.h"


namespace VM {
    class RunMacroCommand: public ClonableCommand <UndoableCommand, RunMacroCommand> {
        char key;
        std::vector<std::unique_ptr<Command>> sequence;

        void doTheCommand(Controller &controller) override;
        void undoTheCommand(Controller &controller) const override;
        void redoTheCommand(Controller &controller) const override;

        public:
        RunMacroCommand(size_t quant, char key);
        RunMacroCommand(const RunMacroCommand&);
        RunMacroCommand(RunMacroCommand&&);
    };

}


#endif
