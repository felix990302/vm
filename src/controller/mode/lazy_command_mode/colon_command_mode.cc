#include <cstdlib>
#include "utility/trim.h"
#include "model/file_buffer.h"
#include "model/file_exception.h"
#include "controller/controller.h"
#include "controller/quit_exception.h"
#include "controller/mode/parsing_exception.h"
#include "controller/command/write_command.h"
#include "controller/command/read_in_command.h"
#include "controller/command/quit_command.h"
#include "controller/command/move_command.h"
#include "controller/command/motion/absolute_motion.h"
#include "controller/command/set_lines_command.h"
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
                return std::make_unique<WriteCommand>(false);return 0;
            }
            else {
                return std::make_unique<WriteCommand>(false, argument);
            }
        }
        else if(command == "r") {
            if(argument.empty()) {
                return std::make_unique<ReadInCommand>();
            }
            else {
                return std::make_unique<ReadInCommand>(argument);
            }
        }
        else if(command == "set") {
            if(argument=="number")
                return std::make_unique<SetLinesCommand>(true);
            else if(argument == "nonumber")
                return std::make_unique<SetLinesCommand>(false);
        }
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
                    return std::make_unique<MoveCommand>(1, std::make_unique<AbsoluteMotion>(lineTarget-1));
                }
                else {
                    throw InvalidCommandException {};
                }
            }
        }
        
        throw InvalidCommandException{};
    }

    char ColonCommandMode::getStatusBarLeftIndicatorChar() {return ':';}

    void ColonCommandMode::flush() {
        trim(commandString);
        size_t seperator = commandString.find_first_of(whitespaces);
        std::string command = commandString.substr(0, seperator);
        std::string argument = seperator < commandString.size() ? commandString.substr(seperator) : "";
        ltrim(argument);
        controller.setMessage("");

        try {
            controller.runCommand(parseCommand(command, argument));
        }
        catch(const InvalidCommandException& e) {
            controller.setMessage("E: Not an editor command: " + e.command);
        }
        catch(const FileWriteException& e) {
            controller.setMessage("E: Unable to write to the file " + e.filename);
        }
        catch(const FileReadException& e) {
            controller.setMessage("Can't open / read file \"" + e.filename +"\"");}
        catch(const ProgramQuitException&) {
            controller.setMessage("E: No write since last change (add ! to override)");}
    }
}
