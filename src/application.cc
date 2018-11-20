#include "application.h"

int main(int argc, char *argv[]) {
    VM::Application app(argc, argv);
    app.run();
}

namespace VM {
    Application::Application(int argc, char **argv) : argc(argc), argv(argv) {}

    void Application::run() {

    }
}