#include "controller/ncurses_input.h"
#include "model/file_buffer.h"
#include "controller/ncurses_input.h"
#include "controller/controller.h"
#include "view/n_curses_display.h"
#include "view/main_view.h"
#include "application.h"

int main(int argc, char *argv[]) {
    if(argc > 1) {
        for(int k=1; k<argc; ++k) {
            VM::Application app {argv[k], VM::make_bufferType(argv[k])}; // copy ellision :)
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
        controller{std::make_unique<Controller>(std::make_unique<NCursesInput>(), fileBuffer.get())},
        mainView(std::make_shared<MainView>(fileBuffer.get(), controller.get())),
        input(controller->getInput())
    {
        display->setMainComponent(mainView);
        NCursesDisplay::resizeHandler(1);

    }

    Application::Application(const std::string &fileName, const BufferType &buffer):
        fileBuffer(std::make_unique<FileBuffer>(fileName, buffer)),
        display(&NCursesDisplay::getMainDisplay()),
        controller{std::make_unique<Controller>(std::make_unique<NCursesInput>(), fileBuffer.get())},
        mainView(std::make_shared<MainView>(fileBuffer.get(), controller.get())),
        input(controller->getInput())
    {
        display->setMainComponent(mainView);
        NCursesDisplay::resizeHandler(1);

    }

    void Application::run() {
        while(*controller) {
            controller->getAndProcessChar();
            display->redraw();
        }
    }

    Application::~Application() {}
}
