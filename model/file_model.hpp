#pragma once

#include "../multiline/code_block.hpp"

#include <vector>
#include <string>

class FileModel {
public:
    FileModel() = default;

    ~FileModel() = default;

    void add_header(const std::string &);

    void add_code_block(const CodeBlock &);

    void update_last_statement(const std::string &);

    [[nodiscard]] const std::vector<std::string> &get_headers() const;

    [[nodiscard]] const std::vector<CodeBlock> &get_code_blocks() const;

    [[nodiscard]] const std::string &get_last_statement() const;

private:
    std::vector<std::string> headers;
    std::vector<CodeBlock> code_blocks;
    std::string last_statement;
};
