#ifndef COMMAND_MODE_H
#define COMMAND_MODE_H

#include "mode.h"
#include <string>
#include <unordered_map>
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
            std::unordered_map<int, std::function<std::unique_ptr<Motion>(int, char)>> motionsParser;
            std::unordered_map<int, std::function<std::unique_ptr<Command>(int)>> commandParser;
            std::unordered_map<int, std::function<std::unique_ptr<Command>(int, std::unique_ptr<Motion>&&)> > commandWithMotionParser;
            enum class ParserStages{
                EarlyStage,
                QuantifierStage,
                CommandStage,
                MotionStage
            };

            Controller &controller;

            ParserHelper(Controller &controller);
        };
        std::unique_ptr<Command> parse();
        std::unique_ptr<Motion> parseMotion(const std::string &, char);

        public:
        ParserHelper parserHelper;

        void processChar(int c) override;
        void flush() override {/*TODO: flush current command sequence*/}
        void onExit() override;

        std::string getStatusBarLeft() override;

        std::string getStatusBarRight() override;


        CommandMode(Controller &controller):
            Mode(controller),
            parserHelper{controller}
        {}
    };
}

#endif
