#ifndef INSERT_MODE_BUFFER_TYPE_H
#define INSERT_MODE_BUFFER_TYPE_H

#include <deque>
#include <memory>
#include "controller/command/undoable_command.h"


namespace VM {
    typedef std::deque<std::unique_ptr<UndoableCommand>> InsertModeBufferType;
}

#endif
