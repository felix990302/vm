#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "text_display.h"
#include "ncurses_input.h"
#include "buffer_view.h"
#include "buffer_type.h"
#include "controller.h"
#include "file_buffer.h"



namespace VM {

    class Application {
    private:
        int argc;
        char **argv;
        //Controller controller;
        TextDisplay * display;
        FileBuffer fileBuffer;
        std::shared_ptr<BufferView> bufferView;
        NCursesInput nCursesInput;

    public:
        Application();
        void run(int argc, char *argv[]);
    };

}


#endif
