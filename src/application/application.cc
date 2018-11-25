#include "application.h"
#include "controller/ncurses_input.h"
#include "controller/insert_mode.h"
#include "view/n_curses_display.h"

int main(int argc, char *argv[]) {
    if(argc > 1) {
        for(int k=1; k<argc; ++k) {
            VM::Application app {argv[k]};
            app.run();
        }
    }
    else {
        VM::Application app {};
        app.run();
    }
}

namespace VM {
    Application::Application():
        fileBuffer(std::make_unique<FileBuffer>()),
        display(&NCursesDisplay::getMainDisplay()),
        bufferView(std::make_shared<BufferView>(fileBuffer.get())),
        controller{std::make_unique<Controller>(std::make_unique<NCursesInput>(), fileBuffer.get())},
        input(controller->getInput())
    {
        display->setMainComponent(bufferView);
        NCursesDisplay::resizeHandler(1);

    }

    Application::Application(const std::string &fileName):
        fileBuffer(std::make_unique<FileBuffer>(fileName)),
        display(&NCursesDisplay::getMainDisplay()),
        bufferView(std::make_shared<BufferView>(fileBuffer.get())),
        controller{std::make_unique<Controller>(std::make_unique<NCursesInput>(), fileBuffer.get())},
        input(controller->getInput())
    {
        display->setMainComponent(bufferView);
        NCursesDisplay::resizeHandler(1);

    }

    void Application::run() {
        while(controller->getAndProcessChar()) {
            display->redraw();
        }
    }
}
