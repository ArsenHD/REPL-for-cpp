#include "code_block.hpp"
#include <iostream>
#include <stdexcept>

void CodeBlock::add_line(const std::string& line) {
    lines_.push_back(line);
}

void CodeBlock::write_to(std::ofstream &file) const {
    for (const std::string& s : lines_){
        file << s << std::endl;
    }
    file << std::endl;
}

CodeBlock CodeBlock::read_block() {
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

std::vector<std::string> CodeBlock::get_lines() const {
    return lines_;
}
