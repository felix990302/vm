#ifndef TOGGLE_RECORD_MACRO_COMMAND_H
#define TOGGLE_RECORD_MACRO_COMMAND_H

#include "controller/command/command.h"


namespace VM {
    class ToggleRecordMacroCommand: public ClonableCommand<Command, ToggleRecordMacroCommand> {
        char key;

        public:
        void doCommand(Controller &controller) override;

        ToggleRecordMacroCommand(char c): Clonable{static_cast<size_t>(1)}, key{c} {}
        ToggleRecordMacroCommand(const ToggleRecordMacroCommand &other): Clonable{other}, key{other.key} {}
        ToggleRecordMacroCommand(ToggleRecordMacroCommand &&other): Clonable{std::move(other)}, key{std::move(other.key)} {}
    };
}

#endif
