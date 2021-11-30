#pragma once

#include "../model/file_model.hpp"

#include <string>
#include <vector>

namespace Options {
    enum Flag {
        SIGNATURE,
        LOAD, // #include
        CREATE_OBJECT,
        EVAL,
        EXIT,
        DEFAULT
    };

    Flag check_for_flag(const std::string &line);

    void load_header(std::string &line, FileModel &includes);

    std::string parse_after_flag(const std::string&);
}