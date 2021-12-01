#include "flags.hpp"

FLAG check_for_flag(const std::string& line){
    if (line.rfind(":s") == 0){
        return SIGNATURE;
    }
    if (line.rfind(":l") == 0){
        return LOAD;
    }
    if (line.rfind(":{") == 0){
        return CREATE_OBJECT;
    }
    if (line.rfind(":e") == 0){
        return EXIT;
    }
    return DEFAULT;
}

void load(std::string& line, std::vector<std::string>& includes){
    std::size_t last = line.find(' ');
    line.erase(0, last + 1);
    std::string input = "#include <" + line + ">";
    includes.push_back(input);
}
