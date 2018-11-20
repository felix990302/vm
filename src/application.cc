#include "application.h"
#include "n_curses_display.h"

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
        controller(),
        display(&NCursesDisplay::getMainDisplay())
    {}

    void Application::run() {

    }
}
