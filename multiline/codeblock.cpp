#include "codeblock.hpp"
#include <iostream>
#include <stdexcept>

void CodeBlock::add_line(const std::string& line) {
    lines.push_back(line);
}

void CodeBlock::add_to_file(std::ofstream &file) {
    for (const std::string& s : lines){
        file << s << std::endl;
    }
    file << std::endl;
}

CodeBlock CodeBlock::create_block() {
    CodeBlock block;
    std::string current_line;
    while (getline(std::cin, current_line)){
        if (current_line.rfind("}:") == 0){
            return block;
        }
        block.add_line(current_line);
    }
    throw std::invalid_argument("Multiline input interrupted.");
}

std::vector<std::string> CodeBlock::data() {
    return lines;
}
