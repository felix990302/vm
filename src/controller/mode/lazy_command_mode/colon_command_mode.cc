#include <cstdlib>
#include "utility/trim.h"
#include "model/file_buffer.h"
#include "model/write_exception.h"
#include "controller/controller.h"
#include "controller/quit_exception.h"
#include "controller/mode/parsing_exception.h"
#include "controller/command/write_command.h"
#include "controller/command/quit_command.h"
#include "controller/command/move_command.h"
#include "controller/command/motion/absolute_motion.h"
#include "colon_command_mode.h"


namespace VM {
    std::unique_ptr<Command> ColonCommandMode::parseCommand(const std::string &command, const std::string &argument) {
        if(command == "wq") {
            if(argument.empty()) {
                return std::make_unique<WriteCommand>(true);
            }
            else {
                return std::make_unique<WriteCommand>(true, argument);
            }
        }
        else if(command == "w") {
            if(argument.empty()) {
                return std::make_unique<WriteCommand>(false);
            }
            else {
                return std::make_unique<WriteCommand>(false, argument);
            }
        }
        else if(command == "r") {}
        else if(argument.empty()) {
            if(command == "q") {
                return std::make_unique<QuitCommand>(false);
            }
            else if(command == "q!") {
                return std::make_unique<QuitCommand>(true);
            }
            else if(command == "$") {
                return std::make_unique<MoveCommand>(1, std::make_unique<AbsoluteMotion>(controller.getBuffer().getBuffer().size()-1));
            }
            else if(command == "0") {
                return std::make_unique<MoveCommand>(1, std::make_unique<AbsoluteMotion>(0));
            }
            else {
                char *end;
                long int lineTarget = strtol(command.c_str(), &end, 10);
                if(lineTarget && *end=='\0') {
                    return std::make_unique<MoveCommand>(1, std::make_unique<AbsoluteMotion>(lineTarget));
                }
                else {
                    throw InvalidCommandException {};
                }
            }
        }
        
        throw InvalidCommandException{};
    }

    void ColonCommandMode::flush() {
        trim(commandString);
        size_t seperator = commandString.find_first_of(whitespaces);
        std::string command = commandString.substr(0, seperator);
        std::string argument = commandString.substr(seperator);
        ltrim(argument);

        try {
            std::unique_ptr<Command> theCommand = parseCommand(command, argument);
            theCommand->doCommand(controller);
        }
        catch(const InvalidCommandException&) {}
        catch(const FileWriteException&) {}
        catch(const ProgramQuitException&) {}
    }
}
