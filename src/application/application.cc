#include "application.h"
#include "controller/ncurses_input.h"
#include "controller/insert_mode.h"
#include "view/n_curses_display.h"

int main(int argc, char *argv[]) {
    VM::Application app {argc, argv};
    app.run();
}

namespace VM {
    Application::Application(int argc, char **argv):
        argc(argc),
        argv(argv),
        fileBuffer(std::make_unique<FileBuffer>()),
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
