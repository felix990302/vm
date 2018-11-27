#include <cstdlib>
#include "utility/trim.h"
#include "controller/mode/parsing_exception.h"
#include "colon_command_mode.h"


namespace VM {
    std::unique_ptr<Command> ColonCommandMode::parseCommand(const std::string &command, const std::string &argument) {
        if(command == "wq") {}
        else if(command == "w") {}
        else if(command == "r") {}
        else if(argument.empty()) {
            if(command == "q") {}
            else if(command == "q!") {}
            else if(command == "$") {}
            else if(command == "0") {}
            else {
                char *end;
                long int lineTarget = strtol(command.c_str(), &end, 10);
                if(lineTarget && *end=='\0') {}
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

        try {
            std::unique_ptr<Command> theCommand = parseCommand(command, argument);
            theCommand->doCommand(controller);
        }
        catch(const InvalidCommandException&) {}
    }
}
