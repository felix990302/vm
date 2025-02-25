#include "controller/command/mutate_command/delete_forward_command.h"
#include "controller/command/mutate_command/delete_backward_command.h"

#include "controller/command/dot_command.h"
#include "controller/command/undo_command.h"
#include "controller/command/redo_command.h"
#include "controller/command/replace_char_command.h"
#include "controller/command/delete_command.h"

#include "controller/command/clipboard_command/paste_command.h"
#include "controller/command/clipboard_command/yank_command.h"

#include "controller/command/macro/toggle_record_macro_command.h"
#include "controller/command/macro/run_macro_command.h"

#include "controller/command/switch_command/enter_search_command.h"
#include "controller/command/switch_command/enter_colon_command.h"
#include "controller/command/switch_command/enter_insert_command.h"
#include "controller/command/switch_command/enter_replace_command.h"
#include "controller/command/switch_command/open_line_insert_command.h"
#include "controller/command/switch_command/eol_enter_insert_command.h"
#include "controller/command/switch_command/bol_enter_insert_command.h"
#include "controller/command/switch_command/right_enter_insert_command.h"
#include "controller/command/switch_command/delete_line_insert_command.h"
#include "controller/command/switch_command/delete_char_insert_command.h"

#include "controller/command/motion/direction_motion.h"
#include "controller/command/motion/word_motion.h"
#include "controller/command/motion/match_brace_motion.h"

#include "controller/command/motion/line_motion/find_motion.h"
#include "controller/command/motion/line_motion/eol_motion.h"
#include "controller/command/motion/line_motion/beg_line_motion.h"
#include "controller/command/motion/line_motion/first_char_motion.h"
#include "controller/command/join_lines.h"

#include "controller/command/information_command.h"

#include "controller/command/move_screen_command.h"

#include "controller/controller.h"
#include "command_mode.h"


namespace VM {
    CommandMode::ParserHelper::ParserHelper(Controller &controller) :
            motionsParser{
                    {'h', [](int quantifier, char) {
                        return std::make_unique<DirectionMotion<Direction::LEFT>>(quantifier);
                    }},
                    {'j', [](int quantifier, char) {
                        return std::make_unique<DirectionMotion<Direction::DOWN>>(quantifier);
                    }},
                    {'k', [](int quantifier, char) { return std::make_unique<DirectionMotion<Direction::UP>>(quantifier); }},
                    {'l', [](int quantifier, char) {
                        return std::make_unique<DirectionMotion<Direction::RIGHT>>(quantifier);
                    }},
                    {'$', [](int quantifier, char) { return std::make_unique<EOLMotion>(quantifier); }},
                    {'0', [](int quantifier, char) { return std::make_unique<BegLineMotion>(quantifier); }},
                    {'^', [](int quantifier, char) { return std::make_unique<FirstCharMotion>(quantifier); }},
                    {'f', [motionsParser = std::ref(motionsParser)](int quantifier, char) {
                        char target = getchar();
                        motionsParser.get().erase(';');
                        motionsParser.get().emplace(';', std::function<std::unique_ptr<Motion>(int,char)>(
                                [oldQuant = quantifier, target = target](int quantifier, char) {
                                    if (quantifier == 1)
                                        return std::make_unique<FindMotion<Direction::RIGHT>>(oldQuant, target);
                                    return std::make_unique<FindMotion<Direction::RIGHT>>(quantifier, target);
                                }));
                        return std::make_unique<FindMotion<Direction::RIGHT>>(quantifier, target);
                    }},
                    {'F', [motionsParser = std::ref(motionsParser)](int quantifier, char) {
                        char target = getchar();
                        motionsParser.get().erase(';');
                        motionsParser.get().emplace(';', std::function<std::unique_ptr<Motion>(int, char)>(
                                [oldQuant = quantifier, target = target](int quantifier, char) {
                                    if (quantifier == 1)
                                        return std::make_unique<FindMotion<Direction::LEFT>>(oldQuant, target);
                                    return std::make_unique<FindMotion<Direction::LEFT>>(quantifier, target);
                                }));
                        return std::make_unique<FindMotion<Direction::LEFT>>(quantifier, target);
                    }},
                    {'%', [](int quantifier, char) { return std::make_unique<MatchBraceMotion>(quantifier); }},
                    {'b', [](int quantifier, char) { return std::make_unique<WordMotion<Direction::LEFT>>(quantifier); }},
                    {'w', [](int quantifier, char) { return std::make_unique<WordMotion<Direction::RIGHT>>(quantifier); }},
            },
            commandParser{
                    {'i', [](int i) { return std::make_unique<EnterInsertCommand>(i); }},
                    {'I', [](int i) { return std::make_unique<BOLEnterInsertCommand>(i); }},
                    {'O', [](int i) { return std::make_unique<OpenLineInsertCommand<Direction::UP>>(i); }},
                    {'o', [](int i) { return std::make_unique<OpenLineInsertCommand<Direction::DOWN>>(i); }},
                    {'A', [](int i) { return std::make_unique<EOLEnterInsertCommand>(i); }},
                    {'a', [](int i) { return std::make_unique<RightEnterInsertCommand>(i); }},
                    {'S', [](int i) { return std::make_unique<DeleteLineInsertCommand>(i); }},
                    {'s', [](int i) { return std::make_unique<DeleteCharInsertCommand>(i); }},
                    {'u', [](int i) { return std::make_unique<UndoCommand>(i); }},
                    {'r' - 96, [](int i) { return std::make_unique<RedoCommand>(i); }},
                    {'r', [](int){char c=getchar(); return std::make_unique<ReplaceCharCommand>(c);}},
                    {'R', [](int i) { return std::make_unique<EnterReplaceCommand>(i); }},
                    {'.', [](int i) { return std::make_unique<DotCommand>(i); }},
                    {':', [](int) { return std::make_unique<EnterColonCommand>(); }},
                    {'/', [](int) { return std::make_unique<EnterSearchCommand<Direction::DOWN>>(); }},
                    {'?', [](int) { return std::make_unique<EnterSearchCommand<Direction::UP>>(); }},
                    {'x', [](int i) { return std::make_unique<DeleteCommand>(1, std::make_unique<DirectionMotion<Direction::RIGHT>> (i)); }},
                    {'X', [](int i) { return std::make_unique<DeleteCommand>(1, std::make_unique<DirectionMotion<Direction::LEFT>> (i)); }},
                    {'p', [](int quantifier) { return std::make_unique<PasteCommand>(quantifier, true); }},
                    {'P', [](int quantifier) { return std::make_unique<PasteCommand>(quantifier, false); }},
                    {'q', [controller = std::ref(controller)](int) {
                        char c=0;
                        if(!controller.get().getMacroRecKey()) c=getchar();
                        return std::make_unique<ToggleRecordMacroCommand>(c);
                    }},
                    {'@', [](int quantifier) { char c=getchar(); return std::make_unique<RunMacroCommand>(quantifier, c); }},
                    {'f' - 96, [](int quantifier) { return std::make_unique<MoveScreenCommand>(quantifier, false); }},
                    {'b' - 96, [](int quantifier) { return std::make_unique<MoveScreenCommand>(quantifier, true); }},
                    {'d' - 96, [](int quantifier) { return std::make_unique<MoveHalfScreenCommand>(quantifier, false); }},
                    {'u' - 96, [](int quantifier) { return std::make_unique<MoveHalfScreenCommand>(quantifier, true); }},
                    {'g' - 96, [](int quantifier) { return std::make_unique<InformationCommand>(quantifier); }},
                    {'J', [](int i) { return std::make_unique<JoinLines>(i); }},
            },
            commandWithMotionParser{
                    {'d', [](int i, std::unique_ptr<Motion> && m) { return std::make_unique<DeleteCommand>(i, std::move(m)); }},
                    {'c', [](int i, std::unique_ptr<Motion> && m) { return std::make_unique<DeleteCommand>(i, std::move(m)); }},
                    {'y', [](int i, std::unique_ptr<Motion> && m) { return std::make_unique<YankCommand>(i, std::move(m)); }},
            },
            controller{controller}
    {}
}
