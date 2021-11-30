#include "flags.hpp"

Options::Flag Options::check_for_flag(const std::string& line){
    if (line.rfind(":s") == 0){
        return SIGNATURE;
    }
    if (line.rfind(":l") == 0){
        return LOAD;
    }
    if (line.rfind(":{") == 0){
        return CREATE_OBJECT;
    }
    if (line.rfind(":e") == 0) {
        return EVAL;
    }
    if (line.rfind("exit") == 0){
        return EXIT;
    }
    return DEFAULT;
}

void Options::load_header(std::string& line, FileModel& file){
    std::size_t space_pos = line.find(' ');
    std::string header = line.substr(space_pos + 1);
    std::string include = "#include <" + header + ">";
    file.add_header(include);
}

std::string Options::parse_after_flag(const std::string &line) {
    std::size_t space_pos = line.find(' ');
    return line.substr(space_pos + 1);
}
