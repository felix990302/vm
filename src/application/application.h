#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include "model/buffer_type.h"


namespace VM {
    class FileBuffer;
    class Controller;
    class MainView;
    class TextDisplay;
    class Input;

    class Application {
    private:
        std::unique_ptr<FileBuffer> fileBuffer;
        TextDisplay * display;
        std::unique_ptr<Controller> controller;
        std::shared_ptr<MainView> mainView;
        const Input *input;

    public:
        Application();
        Application(const std::string &fileName, const BufferType &buffer);
        void run();

        ~Application();
    };
}


#endif
