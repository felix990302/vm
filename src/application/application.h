#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "view/text_display.h"
#include "controller/input.h"
#include "view/buffer_view.h"
#include "model/file_buffer.h"
#include "model/buffer_type.h"
#include "controller/controller.h"



namespace VM {

    class Application {
    private:
        int argc;
        char **argv;
        std::unique_ptr<FileBuffer> fileBuffer;
        BufferView bufferView;
        std::unique_ptr<Controller> controller;
        Input *input;
        TextDisplay * display;


    public:
        Application(int argc, char *argv[]);
        void run();
    };

}


#endif
