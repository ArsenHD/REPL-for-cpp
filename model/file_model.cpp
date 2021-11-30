#include "file_model.hpp"


void FileModel::add_header(const std::string &header) {
    headers.push_back(header);
}

void FileModel::add_code_block(const CodeBlock &code_block) {
    code_blocks.push_back(code_block);
}

void FileModel::update_last_statement(const std::string &statement) {
    last_statement = statement;
}

const std::vector<std::string> &FileModel::get_headers() const {
    return headers;
}

const std::vector<CodeBlock> &FileModel::get_code_blocks() const {
    return code_blocks;
}

const std::string &FileModel::get_last_statement() const {
    return last_statement;
}
