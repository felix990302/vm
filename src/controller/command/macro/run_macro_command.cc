#include "controller/controller.h"
#include "run_macro_command.h"


namespace VM {
    void RunMacroCommand::doTheCommand(Controller &controller) {
        for(size_t k=0; k<quant; ++k) {
            for(auto &commandPair : controller.getMacroMap()[key]) {
                sequence.push_back(commandPair->clone());
                sequence.back()->doCommand(controller);
            }
        }
    }

    void RunMacroCommand::undoTheCommand(Controller &controller) const {
        size_t k=sequence.size();
        while(k--) {
            UndoableCommand *holder = dynamic_cast<UndoableCommand *>(sequence[k].get());
            if(holder) {
                holder->undoCommand(controller);
            }
        }
    }

    void RunMacroCommand::redoTheCommand(Controller &controller) const {
        for(size_t k=0; k<sequence.size(); ++k) {
                UndoableCommand *holder = dynamic_cast<UndoableCommand *>(sequence[k].get());
                if(holder) {
                    holder->redoCommand(controller);
                }
        }
    }

    RunMacroCommand::RunMacroCommand(size_t quant, char key): Clonable{quant}, key{key}, sequence{} {}
    RunMacroCommand::RunMacroCommand(const RunMacroCommand &other):
        Clonable{other},
        key{other.key},
        sequence{}
    {
        for(auto &command : other.sequence) {
            sequence.push_back(command->clone());
        }
    }

    RunMacroCommand::RunMacroCommand(RunMacroCommand &&other):
        Clonable{std::move(other)},
        key{std::move(other.key)},
        sequence{std::move(other.sequence)}
    {}
}
