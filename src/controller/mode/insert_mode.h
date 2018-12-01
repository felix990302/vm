#ifndef INSERT_MODE_H
#define INSERT_MODE_H

#include "insert_mode_buffer_type.h"
#include "mode.h"


namespace VM {
    class ExitHandler;

    class InsertMode: public Mode {
        InsertModeBufferType insertBuffer;
        std::unique_ptr<ExitHandler> exitHandler;


        InsertMode(const InsertMode &other) = delete; // no copies
        InsertMode &operator=(const InsertMode &other) = delete; // no assignment

        public:
        void processChar(int c) override;
        void flush() override;
        void onExit() override;

        void setExitHandler(std::unique_ptr<ExitHandler> handler);
        InsertModeBufferType &getInserBuffer() {return insertBuffer;}

        std::string getStatusBarLeft() override;

        InsertMode(Controller &controller);

        ~InsertMode();
    };
}

#endif
