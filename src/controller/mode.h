#ifndef MODE_H
#define MODE_H


namespace VM {
    class Controller;

    class Mode {
        protected:
        Controller &controller;

        public:
        virtual bool processChar(int c) = 0; // indicate if exit signal was received
        virtual void flush() = 0; // flush state etc
        virtual void onExit() = 0; // exit hook

        Mode(Controller &controller): controller(controller) {}
    };
}

#endif
