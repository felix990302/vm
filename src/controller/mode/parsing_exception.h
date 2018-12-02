#include <string>
namespace VM {
    struct ParsingException {};
    struct UnfinishedCommandException : public ParsingException {};
    struct InvalidCommandException : public ParsingException {
        std::string command;
    };
}
