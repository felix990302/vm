#ifndef TRIM_H
#define TRIM_H

#include <string>


namespace VM {
    static constexpr char whitespaces[] = "\t\n\v\f\r ";

    std::string &ltrim(std::string &str, const std::string &chars=whitespaces);

    std::string &rtrim(std::string &str, const std::string &chars=whitespaces);

    std::string &trim(std::string &str, const std::string &chars=whitespaces);
}

#endif
