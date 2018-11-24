#ifndef MODE_H
#define MODE_H


namespace VM {
    class Controller;

    class Mode {
        protected:
        Controller &controller;

        public:
        virtual void processChar(int c) = 0;

        Mode(Controller &controller): controller(controller) {}
    };
}

#endif
