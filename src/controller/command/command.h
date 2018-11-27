#ifndef COMMAND_H
#define COMMAND_H

#include <memory>


namespace VM {
    class Cursor;
    class Controller;

    class Command {
        protected:
        const size_t quant;

        public:
        virtual void doCommand(Controller &controller) = 0;

        Command(size_t quant=1);
        virtual std::unique_ptr<Command> clone() const = 0;
        virtual ~Command() = 0;
    };

    template<typename Base, typename Sub> class ClonableCommand: public Base {
        public:
        std::unique_ptr<Command> clone() const override final {
            return std::make_unique<Sub>(static_cast<const Sub &>(*this));
        }

        template<typename ...Args> ClonableCommand(Args ...args): Base{args...} {}
    };
}

#endif
