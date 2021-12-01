#pragma once
#include <string>
#include <vector>
#include <fstream>

class CodeBlock{
private:
    std::vector<std::string> lines;

public:
    CodeBlock() = default;
    ~CodeBlock() = default;
    void add_line(const std::string& line);
    static CodeBlock create_block();
    void add_to_file(std::ofstream &file);
    std::vector<std::string> data();
};
