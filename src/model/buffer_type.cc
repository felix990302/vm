#include <fstream>
#include "file_exception.h"
#include "buffer_type.h"


namespace VM {
    BufferType make_bufferType(const std::string &fileName) {
        BufferType buffer;
        std::string temp;
        std::ifstream file {fileName};

        if(!file) throw FileReadException {};

        while(getline(file, temp)) {
            buffer.push_back(std::move(temp));
        }
        if(buffer.empty()) buffer.emplace_back();

        return buffer;
    }
}
