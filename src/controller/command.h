#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include "model/cursor.h"


class Cursor;

namespace VM {
    class Command {
        const size_t quant;
        Cursor appliedPosn;

        protected:
        virtual void doTheCommand() = 0;
        const Cursor &getAppliedPosn();

        public:
        void doCommand(const Cursor &currentCursor);

        Command(const size_t &quant);
        virtual std::unique_ptr<Command> clone() const = 0;
        virtual ~Command() = 0;
    };
}

#endif
