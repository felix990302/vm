#ifndef COMMAND_H
#define COMMAND_H

#include <memory>


namespace VM {
    class Cursor;
    class Controller;

    class Command {
        const size_t quant;

        protected:
        virtual void doTheCommand(Controller &controller) const = 0;
        virtual void doTheSideEffect(Controller &controller) = 0;

        public:
        size_t getQuant() const {return quant;}
        void doCommand(Controller &controller);

        Command(size_t quant=1);
        virtual std::unique_ptr<Command> clone() const = 0;
        virtual ~Command() = 0;
    };
}

#endif
