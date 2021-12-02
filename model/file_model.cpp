#include "file_model.hpp"
#include "../utils/ast_utils.hpp"
#include <algorithm>

void FileModel::add_header(const std::string &header) {
    headers.push_back(header);
}

void FileModel::add_code_block(const CodeBlock &code_block) {
    code_blocks.push_back(code_block);
}

void FileModel::add_variable_declaration(const std::string &declaration) {
    variable_declarations.push_back(declaration);
    std::string variable_name = AstUtils::parse_variable_name(declaration);
    variable_name_by_declaration.insert(std::make_pair(declaration, variable_name));
}

void FileModel::update_last_statement(const std::string &statement) {
    last_statement = statement;
}

std::string FileModel::get_variable_name_by_declaration(const std::string &declaration) {
    return variable_name_by_declaration[declaration];
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

const std::vector<std::string> &FileModel::get_variable_declarations() const {
    return variable_declarations;
}

FileModel& FileModel::operator=(const FileModel& fileModel) {
    FileModel copy(fileModel);
    swap(copy);
    return *this;
}

void FileModel::swap(FileModel &other) {
    std::swap(code_blocks, other.code_blocks);
    std::swap(headers, other.headers);
    std::swap(last_statement, other.last_statement);
}
