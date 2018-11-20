#ifndef APPLICATION_H
#define APPLICATION_H

#include "text_display.h"
#include "ncurses_input.h"
#include "buffer_view.h"
#include "buffer_base.h"
#include "controller.h"

namespace VM {

    class Application {
    private:
        int argc;
        char *argv[];
        BufferView bufferView;
        NCursesInput nCursesInput;
        Controller controller;
        TextDisplay display;


    public:
        Application(int argc, char *argv[]);
        void run();
    };

}


#endif
