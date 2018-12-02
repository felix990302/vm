#include "view/buffer_view.h"
#include "set_lines_command.h"
#include "controller/controller.h"


namespace VM {

    void SetLinesCommand::doCommand(Controller &controller) {
        controller.getBufferView().setLineNumbers(onOrOff);
    }
}