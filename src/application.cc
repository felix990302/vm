#include "application.h"
#include "n_curses_display.h"
#include "buffer_view.h"
#include "file_buffer.h"
#include "buffer_type.h"

int main(int argc, char *argv[]) {
    VM::Application app;
    app.run(argc, argv);
}

namespace VM {

    Application::Application() : display(&NCursesDisplay::getMainDisplay()), fileBuffer(), bufferView(std::make_shared<BufferView>(&fileBuffer)){

    }

    void Application::run(int argc, char **argv) {

    }
}