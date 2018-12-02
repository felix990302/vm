#ifndef REPLACE_MODE_H
#define REPLACE_MODE_H

#include "insert_mode_buffer_type.h"
#include "mode.h"


namespace VM {
    class ExitHandler;

    class ReplaceMode: public Mode {
        InsertModeBufferType insertBuffer;
        std::unique_ptr<ExitHandler> exitHandler;


        ReplaceMode(const ReplaceMode &other) = delete; // no copies
        ReplaceMode &operator=(const ReplaceMode &other) = delete; // no assignment

        public:
        void processChar(int c) override;
        void flush() override;
        void onExit() override;

        void setExitHandler(std::unique_ptr<ExitHandler> handler);
        InsertModeBufferType &getInserBuffer() {return insertBuffer;}

        std::string getStatusBarLeft() override;

        ReplaceMode(Controller &controller);

        ~ReplaceMode();
    };
}

#endif
