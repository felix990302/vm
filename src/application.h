#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "text_display.h"
#include "ncurses_input.h"
#include "buffer_view.h"
#include "file_buffer.h"
#include "buffer_base.h"
#include "controller.h"



namespace VM {

    class Application {
    private:
        int argc;
        char **argv;
        std::unique_ptr<FileBuffer> fileBuffer;
        BufferView bufferView;
        NCursesInput nCursesInput;
        Controller *controller;
        TextDisplay * display;


    public:
        Application(int argc, char *argv[]);
        void run();
    };

}


#endif
