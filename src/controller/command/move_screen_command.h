#ifndef MOVESCREENCOMMAND_H
#define MOVESCREENCOMMAND_H
#include "command.h"
#include "view/buffer_view.h"
#include "controller/controller.h"

namespace VM {

    class MoveScreenCommand : public ClonableCommand<Command, MoveScreenCommand> {
        bool up;
        void doCommand(Controller &controller) override
        {
            for(size_t i = 0; i < quant; ++i) controller.getBufferView().moveScreen(up);
        }

    public:
        MoveScreenCommand(size_t quant, bool up): Clonable{quant}, up{up} {}
        MoveScreenCommand(const MoveScreenCommand &other): Clonable{other}, up{other.up} {};
        MoveScreenCommand(MoveScreenCommand &&other): Clonable{std::move(other)}, up{other.up} {};

    };

    class MoveHalfScreenCommand : public ClonableCommand<Command, MoveHalfScreenCommand> {
        bool up;
        void doCommand(Controller &controller) override
        {
            for(size_t i = 0; i < quant; ++i) controller.getBufferView().moveHalfScreen(up);
        }

    public:
        MoveHalfScreenCommand(size_t quant, bool up): Clonable{quant}, up{up} {}
        MoveHalfScreenCommand(const MoveHalfScreenCommand &other): Clonable{other}, up{other.up} {};
        MoveHalfScreenCommand(MoveHalfScreenCommand &&other): Clonable{std::move(other)}, up{other.up} {};
    };

}


#endif
