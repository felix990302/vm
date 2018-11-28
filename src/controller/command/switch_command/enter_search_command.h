#ifndef ENTER_SEARCH_COMMAND_H
#define ENTER_SEARCH_COMMAND_H

#include "controller/controller.h"
#include "controller/mode/lazy_command_mode/search_command_mode.h"
#include "controller/command/motion/direction.h"
#include "controller/command/command.h"


namespace VM {
    template<Direction dir>class EnterSearchCommand;

    template<>class EnterSearchCommand<Direction::DOWN>: public ClonableCommand<Command, EnterSearchCommand<Direction::DOWN>> {
        public:
        void doCommand(Controller &controller) override {
            controller.changeMode(controller.modes.searchDownMode.get());
        }
    };

    template<>class EnterSearchCommand<Direction::UP>: public ClonableCommand<Command, EnterSearchCommand<Direction::DOWN>> {
        public:
        void doCommand(Controller &controller) override {
            controller.changeMode(controller.modes.searchUpMode.get());
        }
    };
}

#endif
