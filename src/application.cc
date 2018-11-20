#include "application.h"
#include "n_curses_display.h"

int main(int argc, char *argv[]) {
    VM::Application app;
    app.run(argc, argv);
}

namespace VM {

    Application::Application(int argc, char **argv) : argc(argc), argv(argv), display(&NCursesDisplay::getMainDisplay()), bufferView(), controller(){

    }

    void Application::run() {

    }
}