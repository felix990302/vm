namespace VM {
    class ParsingException {};
    class UnfinishedCommandException : public ParsingException {};
    class InvalidCommandException : public ParsingException {};
}
