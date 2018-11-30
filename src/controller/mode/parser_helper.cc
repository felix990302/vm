#include "controller/command/mutate_command/delete_forward_command.h"
#include "controller/command/mutate_command/delete_backward_command.h"
#include "controller/command/dot_command.h"
#include "controller/command/undo_command.h"
#include "controller/command/redo_command.h"
#include "controller/command/switch_command/enter_search_command.h"
#include "controller/command/switch_command/enter_colon_command.h"
#include "controller/command/switch_command/enter_insert_command.h"
#include "controller/command/motion/direction_motion.h"
#include "controller/command/motion/line_motion/find_motion.h"
#include "controller/command/motion/line_motion/eol_motion.h"
#include "controller/command/motion/line_motion/beg_line_motion.h"
#include "controller/command/motion/line_motion/first_char_motion.h"
#include "controller/command/motion/word_motion.h"
#include "command_mode.h"


namespace VM {
    CommandMode::ParserHelper::ParserHelper():
        motionsParser {
            {'h', [](int quantifier){return std::make_unique<DirectionMotion<Direction::LEFT>>(quantifier);}},
            {'j', [](int quantifier){return std::make_unique<DirectionMotion<Direction::DOWN>>(quantifier);}},
            {'k', [](int quantifier){return std::make_unique<DirectionMotion<Direction::UP>>(quantifier);}},
            {'l', [](int quantifier){return std::make_unique<DirectionMotion<Direction::RIGHT>>(quantifier);}},
            {'$', [](int quantifier){return std::make_unique<EOLMotion>(quantifier);}},
            {'0', [](int quantifier){return std::make_unique<BegLineMotion>(quantifier);}},
            {'^', [](int quantifier){return std::make_unique<FirstCharMotion>(quantifier);}},
            {'f', [](int quantifier){char c = getchar(); return std::make_unique<FindMotion<Direction::RIGHT>>(quantifier, c);}}, //TODO improve
            {'F', [](int quantifier){char c = getchar(); return std::make_unique<FindMotion<Direction::LEFT>>(quantifier, c);}},
            {'b', [](int quantifier){return std::make_unique<WordMotion<Direction::LEFT>>(quantifier);}},
            {'w', [](int quantifier){return std::make_unique<WordMotion<Direction::RIGHT>>(quantifier);}},
        },
        commandParser {
            {'i', [](int){ return std::make_unique<EnterInsertCommand>();}},
            {'u', [](int i){ return std::make_unique<UndoCommand>(i);}},
            {'r'-96, [](int i){ return std::make_unique<RedoCommand>(i);}},
            {'.', [](int i){ return std::make_unique<DotCommand>(i);}},
            {':', [](int){ return std::make_unique<EnterColonCommand>();}},
            {'/', [](int){ return std::make_unique<EnterSearchCommand<Direction::DOWN>>();}},
            {'?', [](int){ return std::make_unique<EnterSearchCommand<Direction::UP>>();}},
            {'x', [](int i){ return std::make_unique<DeleteForwardCommand>(i);}},
            {'X', [](int i){ return std::make_unique<DeleteBackwardCommand>(i);}},
        },
        commandWithMotionParser{}
    {}
}
