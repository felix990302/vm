#ifndef BUFFER_BASE_H
#define BUFFER_BASE_H

#include <vector>
#include <string>

namespace VM {
    typedef std::string LineType;
    typedef std::vector<LineType> BufferType;

    typedef BufferType BufferBase;
}

#endif

