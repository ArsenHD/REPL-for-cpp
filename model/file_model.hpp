#pragma once

#include "../multiline/code_block.hpp"

#include <vector>
#include <string>
#include <unordered_map>

class FileModel {
public:
    FileModel() = default;

    ~FileModel() = default;

    FileModel(const FileModel &fileModel) :
            headers(fileModel.get_headers()),
            code_blocks(fileModel.get_code_blocks()),
            last_statement(fileModel.get_last_statement()) {}

    FileModel& operator=(const FileModel& fileModel);

    void add_header(const std::string &);

    void add_code_block(const CodeBlock &);

    void add_variable_declaration(const std::string &);

    void update_last_statement(const std::string &);

    std::string get_variable_name_by_declaration(const std::string&);

    [[nodiscard]] const std::vector<std::string> &get_headers() const;

    [[nodiscard]] const std::vector<CodeBlock> &get_code_blocks() const;

    [[nodiscard]] const std::vector<std::string> &get_variable_declarations() const;

    [[nodiscard]] const std::string &get_last_statement() const;


private:
    std::vector<std::string> headers;
    std::vector<CodeBlock> code_blocks;
    std::vector<std::string> variable_declarations;
    // variable names
    std::unordered_map<std::string, std::string> variable_name_by_declaration;
    std::string last_statement;

    void swap(FileModel&);
};
