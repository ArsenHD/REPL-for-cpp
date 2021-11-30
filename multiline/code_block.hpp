#pragma once

#include <string>
#include <vector>
#include <fstream>

class CodeBlock {
public:
    CodeBlock() = default;

    ~CodeBlock() = default;

    void add_line(const std::string &line);

    void write_to(std::ofstream &file) const;

    [[nodiscard]] std::vector<std::string> get_lines() const;

    static CodeBlock read_block();

private:
    std::vector<std::string> lines_;
};
