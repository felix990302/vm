#include "controller/command/dot_command.h"
#include "controller/command/undo_command.h"
#include "controller/command/redo_command.h"
#include "controller/command/switch_command/enter_insert_command.h"
#include "command_mode.h"
#include "controller/command/motion/direction_motion.h"
#include "controller/command/motion/find_motion.h"



namespace VM {
    std::unordered_map<int, std::function<std::unique_ptr<Motion>(int)>>  CommandMode::ParserHelper::motionsParser = {
            {'h', [](int quantifier){return std::make_unique<DirectionMotion<Direction::LEFT>>(quantifier);}},
            {'j', [](int quantifier){return std::make_unique<DirectionMotion<Direction::DOWN>>(quantifier);}},
            {'k', [](int quantifier){return std::make_unique<DirectionMotion<Direction::UP>>(quantifier);}},
            {'l', [](int quantifier){return std::make_unique<DirectionMotion<Direction::RIGHT>>(quantifier);}},
            {'f', [](int quantifier){char c = getchar(); return std::make_unique<FindMotion<Direction::RIGHT>>(quantifier, c);}}, //TODO improve
            {'F', [](int quantifier){char c = getchar(); return std::make_unique<FindMotion<Direction::LEFT>>(quantifier, c);}},
    };
    std::unordered_map<int, std::function<std::unique_ptr<Command>(int)>>  CommandMode::ParserHelper::commandParser = {
            {'i', [](int){ return std::make_unique<EnterInsertCommand>();}},
            {'u', [](int i){ return std::make_unique<UndoCommand>(i);}},
            {'r'-96, [](int i){ return std::make_unique<RedoCommand>(i);}},
            {'.', [](int i){ return std::make_unique<DotCommand>(i);}}
    };
    std::unordered_map<int, std::function<std::unique_ptr<Command>(int, std::unique_ptr<Motion>&&)> >  CommandMode::ParserHelper::commandWithMotionParser = {};
}
