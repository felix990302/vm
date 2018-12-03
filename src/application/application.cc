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
            VM::Application app {argv[k]}; // copy ellision :)
            app.run();
        }
    }
    else {
        VM::Application app {};
        app.run();
    }
}

namespace VM {
    Application::Application(): Application("")
    {}

    Application::Application(const std::string &fileName):
        fileBuffer(std::make_unique<FileBuffer>(fileName)),
        display(&NCursesDisplay::getMainDisplay()),
        controller{std::make_unique<Controller>(std::make_unique<NCursesInput>(), fileBuffer.get(), nullptr)},
        mainView(std::make_shared<MainView>(fileBuffer.get(), controller.get())),
        input(controller->getInput())
    {
        fileBuffer->getBuffer() = createInitialBufferType(fileName);
        display->setMainComponent(mainView);
        controller->setBufferView(&(mainView->getBufferView()));
        NCursesDisplay::resizeHandler(1);
    }

    void Application::run() {
        while(*controller) {
            controller->getAndProcessChar();
            display->redraw();
        }
    }

    Application::~Application() {}

    BufferType Application::createInitialBufferType(const std::string &filename) {
        if(filename.size()==0)
            return BufferType{1};
        try {
            const BufferType &bft = make_bufferType(filename);
            controller->setMessage("\"" + filename + "\" " + std::to_string(bft.size()) + "L");
            return bft;
        }
        catch (...)
        {
            controller->setMessage("\"" + filename + "\" [New File]");
            return BufferType{1};
        }
    }
}
