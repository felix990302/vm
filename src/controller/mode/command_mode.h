#ifndef COMMAND_MODE_H
#define COMMAND_MODE_H

#include "mode.h"
#include <string>
#include <map>
#include <memory>
#include <functional>


namespace VM {
    class Command;
    class Motion;

    class CommandMode: public Mode {
        CommandMode(const CommandMode &other) = delete; // no copies
        CommandMode &operator=(const CommandMode &other) = delete; // no assignment
        std::string commandBuffer;

        struct ParserHelper {
            static std::map<char, std::function<std::unique_ptr<Motion>(int)>> motionsParser;
            static std::map<char, std::function<std::unique_ptr<Command>(int)>> commandParser;
            static std::map<char, std::function<std::unique_ptr<Command>(int, std::unique_ptr<Motion>&&)> > commandWithMotionParser;
            enum class ParserStages{
                EarlyStage,
                QuantifierStage,
                CommandStage,
                MotionStage
            };
            class ParsingException {};
            class UnfinishedCommandException : public ParsingException {};
            class InvalidCommandException : public ParsingException {};
        };

        std::unique_ptr<Command> parse();
        std::unique_ptr<Motion> parseMotion(const std::string &);

        public:
        void processChar(int c) override;
        void flush() override {/*TODO: flush current command sequence*/}
        void onExit() override {flush();}


        CommandMode(Controller &controller): Mode(controller) {}
    };
}

#endif
