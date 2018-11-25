#ifndef MODE_H
#define MODE_H


namespace VM {
    class Controller;

    class Mode {
        protected:
        Controller &controller;

        public:
        virtual void processChar(int c) = 0;
        virtual void flush() = 0; // flush state etc
        virtual void onExit() = 0; // exit hook

        Mode(Controller &controller): controller(controller) {}
    };
}

#endif
