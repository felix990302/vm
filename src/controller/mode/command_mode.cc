#include <memory>
#include "controller/controller.h"
#include "controller/command/switch_command/enter_insert_command.h"
#include "controller/command/move_command.h"
#include "controller/command/motion/direction_motion.h"
#include "controller/command/motion/find_motion.h"
#include "parsing_exception.h"
#include "command_mode.h"


namespace VM {
    void CommandMode::processChar(int c) { //FIXME: generalize parsing
        commandBuffer.push_back(c);
        try {
            controller.runCommand(parse());
            commandBuffer.clear();
        }
        catch (const UnfinishedCommandException &) {}
        catch (const InvalidCommandException &)
        {
            commandBuffer.clear();
        }
    }

    std::unique_ptr<Command> CommandMode::parse() {

        try {
            return std::make_unique<MoveCommand>(1,parseMotion(commandBuffer));
        }
        catch (const ParsingException &) {}

        int quantifier = 1;
        ParserHelper::ParserStages stage = ParserHelper::ParserStages::EarlyStage;

        for(size_t i = 0; i < commandBuffer.length(); ++i)
        {
            const char &c = commandBuffer[i];

            switch (stage) { //identify next stage
                case ParserHelper::ParserStages::EarlyStage:
                    if(isdigit(c) && c != '0')
                        stage = ParserHelper::ParserStages::QuantifierStage, quantifier = 0;
                    else
                        stage = ParserHelper::ParserStages::CommandStage;
                    break;

                case ParserHelper::ParserStages::QuantifierStage:
                    if(!isdigit(c))
                        stage = ParserHelper::ParserStages::CommandStage;
                    break;

                default:
                    break;
            }

            switch (stage) { //parse character
                case ParserHelper::ParserStages::QuantifierStage:
                    quantifier = quantifier * 10 + (c - '0');
                    break;

                case ParserHelper::ParserStages::CommandStage:
                    if(ParserHelper::commandParser.count(c))
                        return  ParserHelper::commandParser[c](quantifier);
                    else if(ParserHelper::commandWithMotionParser.count(c))
                    {
                        return ParserHelper::commandWithMotionParser[c](quantifier, parseMotion(commandBuffer.substr(i+1))); // copy ellision
                    }
                    else
                        throw InvalidCommandException();

                default:
                    break;
            }
        }
        throw UnfinishedCommandException{};
    }

    std::unique_ptr<Motion> CommandMode::parseMotion(const std::string &motionString) {
        //TODO special case for whole line motion
        ParserHelper::ParserStages stage = ParserHelper::ParserStages::EarlyStage;
        int quantifier = 1;
        for(const char &c : motionString)
        {
            switch (stage) { //identify next stage
                case ParserHelper::ParserStages::EarlyStage:
                    if(isdigit(c) && c != '0')
                        stage = ParserHelper::ParserStages::QuantifierStage, quantifier = 0;
                    else
                        stage = ParserHelper::ParserStages::MotionStage;
                    break;

                case ParserHelper::ParserStages::QuantifierStage:
                    if(!isdigit(c))
                        stage = ParserHelper::ParserStages::MotionStage;
                    break;

                default:
                    break;
            }

            switch (stage) { //parse character
                case ParserHelper::ParserStages::QuantifierStage:
                    quantifier = quantifier * 10 + (c - '0');
                    break;

                case ParserHelper::ParserStages::MotionStage:
                    if(ParserHelper::motionsParser.count(c))
                        return  ParserHelper::motionsParser[c](quantifier);
                    else
                        throw InvalidCommandException();

                default:
                    break;
            }
        }
        throw UnfinishedCommandException{};
    }

    std::string CommandMode::getStatusBarLeft() {
        return "";
    }

    std::string CommandMode::getStatusBarRight() {
        return commandBuffer;
    }
}
