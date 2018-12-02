#ifndef MODE_H
#define MODE_H

#include <string>

namespace VM {
    class Controller;

    class Mode {
        protected:
        Controller &controller;

        public:
        virtual void processChar(int c) = 0; 
        virtual void flush() = 0; // flush state etc
        virtual void onExit() = 0; // exit hook

        virtual std::string getStatusBarLeft();
        virtual std::string getStatusBarRight();
        virtual int getStatusBarCursor();

        Mode(Controller &controller): controller(controller) {}



        virtual ~Mode() = 0;
    };
}

#endif
