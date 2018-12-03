#ifndef INFORMATIONCOMMAND_H
#define INFORMATIONCOMMAND_H

#include "command.h"
#include "controller/controller.h"
#include "view/buffer_view.h"
#include "model/file_buffer.h"

namespace VM {

    class InformationCommand :  public ClonableCommand<Command, InformationCommand>{
        void doCommand(Controller &controller) override
        {
            controller.setMessage("\""+
              (controller.getBuffer().getFileName().size()==0
                ?"[No Name]"
                : controller.getBuffer().getFileName())
              + "\" " + std::to_string(controller.getBuffer().getBuffer().size()) + " lines --"
              + std::to_string(100 * (controller.getBuffer().ptrCursor.getLine()+1) / controller.getBuffer().getBuffer().size()) + "%--");
        }

    public:
        InformationCommand(size_t quant): Clonable{quant} {}
        InformationCommand(const InformationCommand &other): Clonable{other} {};
        InformationCommand(InformationCommand &&other): Clonable{std::move(other)} {};
    };

}


#endif
