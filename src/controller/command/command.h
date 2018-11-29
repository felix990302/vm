#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include "utility/clonable.h"


namespace VM {
    class Cursor;
    class Controller;

    class Command {
        protected:
        size_t quant;

        public:
        virtual void doCommand(Controller &controller) = 0;
        size_t getQuant() {return quant;}
        void setQuant(size_t newQ) {quant = newQ;}

        Command(size_t quant=1);
        virtual std::unique_ptr<Command> clone() const = 0;
        virtual ~Command() = 0;
    };

    template<typename Base, typename Sub> using ClonableCommand = Clonable<Command, Base, Sub>;
}

#endif
