#ifndef OPEN_LINE_INSERT_COMMAND
#define OPEN_LINE_INSERT_COMMAND

#include "controller/mode/insert_mode.h"
#include "controller/mode/exit_handler/open_line_handler.h"
#include "controller/controller.h"
#include "controller/command/command.h"
#include "controller/command/mutate_command/open_line_command.h"


namespace VM {
    template<Direction dir> class OpenLineInsertCommand: public ClonableCommand<Command, OpenLineInsertCommand<dir>> {
        public:
        void doCommand(Controller &controller) override {
            controller.changeMode(controller.modes.insertMode.get());
            InsertMode &insertMode = *controller.modes.insertMode;
            insertMode.getInserBuffer().push_back(std::make_unique<OpenLineCommand<dir>>());
            insertMode.getInserBuffer().back()->doCommand(controller);
            insertMode.setExitHandler(std::make_unique<OpenLineHandler>(Command::quant));
        }

        OpenLineInsertCommand(size_t quant): ClonableCommand<Command, OpenLineInsertCommand<dir>>{quant} {}
        OpenLineInsertCommand(const OpenLineInsertCommand &other): ClonableCommand<Command, OpenLineInsertCommand<dir>>{other} {}
        OpenLineInsertCommand(OpenLineInsertCommand &&other): ClonableCommand<Command, OpenLineInsertCommand<dir>>{std::move(other)} {}
        ~OpenLineInsertCommand() {}
    };
}

#endif
