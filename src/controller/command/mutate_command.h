#ifndef MUTATE_COMMAND_H
#define MUTATE_COMMAND_H

#include <string>
#include "model/cursor.h"
#include "undoable_command.h"


namespace VM {
    class MutateCommand: public UndoableCommand {
        std::string toMutate;

        public:
        const std::string &getToMutate() const {return toMutate;}
        void setCursor(const Cursor &newCursor);

        MutateCommand(const size_t &quant, const std::string &toMutate);
        MutateCommand(const MutateCommand &other);
        MutateCommand(MutateCommand &&other);
        virtual ~MutateCommand();
    };
}

#endif
