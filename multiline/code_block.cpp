#include "code_block.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

void CodeBlock::add_line(const std::string& line) {
    lines_.push_back(line);
}

void CodeBlock::write_to(std::ostream &file) const {
    for (const std::string& s : lines_){
        file << s << std::endl;
    }
    file << std::endl;
}

//CodeBlock CodeBlock::read_block() {
std::string CodeBlock::read_block() {
    std::stringstream block;
    std::string current_line;
    while (getline(std::cin, current_line)){
        if (current_line.rfind("}:") == 0){
            return block.str();
        }
        block << current_line << std::endl;
//        block.add_line(current_line);
    }
    throw std::invalid_argument("Multiline input interrupted.");
}

std::vector<std::string> CodeBlock::get_lines() const {
    return lines_;
}
