#include "command.h"
#include "model/cursor.h"


namespace VM {
    const Cursor &Command::getAppliedPosn() {
        return appliedPosn;
    }

    void Command::doCommand(const Cursor &currentCursor) {
        appliedPosn = currentCursor;

        doTheCommand();
    }

    Command::Command(const size_t &quant): quant{quant} {}

    Command::~Command() {}
}
