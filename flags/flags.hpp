#pragma once
#include <string>
#include <vector>

enum FLAG{
    SIGNATURE,
    LOAD, // #include
    CREATE_OBJECT,
    EXIT,
    DEFAULT
};

FLAG check_for_flag(const std::string& line);

void load(std::string& line, std::vector<std::string>& includes);
