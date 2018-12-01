#ifndef SEARCH_COMMAND_MODE_H
#define SEARCH_COMMAND_MODE_H

#include <memory>
#include <functional>
#include "controller/controller.h"
#include "controller/command/motion/search_motion.h"
#include "controller/command/move_command.h"
#include "controller/mode/command_mode.h"
#include "lazy_command_mode.h"


namespace VM {
    template<Direction dir> class SearchCommandMode: public LazyCommandMode {
        char getStatusBarLeftIndicatorChar() override {
            return dir==Direction::DOWN ? '/' : '?';
        }

        public:
        void flush() override {
            controller.runSimpleCommand(std::make_unique<MoveCommand>(1, std::make_unique<SearchMotion<dir>>(1, commandString)));

            controller.modes.commandMode->parserHelper.motionsParser.erase('n');
            controller.modes.commandMode->parserHelper.motionsParser.emplace('n',
                    std::function<std::unique_ptr<Motion>(int)>([commandString = commandString] (int n) {
                        return std::make_unique<SearchMotion<dir>>(n, commandString);
                    })
            );
            controller.modes.commandMode->parserHelper.motionsParser.erase('N');
            controller.modes.commandMode->parserHelper.motionsParser.emplace('N',
                    std::function<std::unique_ptr<Motion>(int)>([commandString = commandString] (int n) {
                        return std::make_unique<SearchMotion<dir==Direction::DOWN ? Direction::UP : Direction::DOWN>>(n, commandString);
                    })
            );
        }

        SearchCommandMode(Controller &controller): LazyCommandMode{controller} {}
    };
}

#endif
