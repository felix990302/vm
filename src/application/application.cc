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
        bufferView(fileBuffer.get()),
        controller{std::make_unique<Controller>(std::make_unique<NCursesInput>(), &InsertMode::Instance(), fileBuffer.get())},
        input(controller->getInput()),
        display(&NCursesDisplay::getMainDisplay())
    {}

    void Application::run() {

    }
}
