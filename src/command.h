#ifndef COMMAND_H
#define COMMAND_H

#include <memory>


namespace VM {
    class Command {
        const size_t quant;

        public:
        virtual void doCommand() = 0;
        virtual std::unique_ptr<Command> clone() = 0;

        Command(const size_t &quant);
        virtual ~Command() = 0;
    };
}

#endif
