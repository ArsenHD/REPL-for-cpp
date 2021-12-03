#include "file_model.hpp"
#include "../utils/ast_utils.hpp"
#include "../utils/code_generator.hpp"

#include <algorithm>
#include <sstream>
#include <iostream>

void FileModel::add_header(const std::string &header) {
    headers.push_back(header);
}

void FileModel::add_function(const std::string &declaration) {
    std::string function_name = AstUtils::parse_name(declaration);
    if (rfunction_name_by_declaration.count(function_name) == 1) {
        auto decl = rfunction_name_by_declaration[function_name];
        function_declarations.erase(decl);
    }
    function_declarations.insert(declaration);
    function_name_by_declaration[declaration] = function_name;
    rfunction_name_by_declaration[function_name] = declaration;
}

void FileModel::add_record(const std::string &declaration) {
    std::string record_name = AstUtils::parse_name(declaration);
    if (rrecord_name_by_declaration.count(record_name) == 1) {
        auto decl = rrecord_name_by_declaration[record_name];
        record_declarations.erase(decl);
    }
    record_declarations.insert(declaration);
    record_name_by_declaration[declaration] = record_name;
    rrecord_name_by_declaration[record_name] = declaration;
}

void FileModel::add_variable_declaration(const std::string &declaration) {
//    variable_declarations.push_back(declaration);
    std::string variable_name = AstUtils::parse_name(declaration);
    if (rvariable_name_by_declaration.count(variable_name) == 1) {
        auto decl = rvariable_name_by_declaration[variable_name];
        variable_declarations.erase(decl);
    }
    variable_declarations.insert(declaration);
//    std::cout << "new variable: " << name << std::endl;
    variable_name_by_declaration[declaration] = variable_name;
    rvariable_name_by_declaration[variable_name] = declaration;
}

void FileModel::update_last_statement(const std::string &statement) {
    last_statement = statement;
}

std::string FileModel::get_variable_name_by_declaration(const std::string &declaration) {
//    for (const auto& e : variable_name_by_declaration) {
//        std::cout << "! " << e.first << " " << e.second << std::endl;
//    }
    return variable_name_by_declaration[declaration];
}

const std::vector<std::string> &FileModel::get_headers() const {
    return headers;
}

//const std::vector<CodeBlock> &FileModel::get_code_blocks() const {
//    return code_blocks;
//}

const std::string &FileModel::get_last_statement() const {
    return last_statement;
}

const std::unordered_set<std::string> &FileModel::get_variable_declarations() const {
    return variable_declarations;
}

const std::unordered_set<std::string> &FileModel::get_function_declarations() const {
    return function_declarations;
}

const std::unordered_set<std::string> &FileModel::get_record_declarations() const {
    return record_declarations;
}


FileModel& FileModel::operator=(const FileModel& fileModel) {
    FileModel copy(fileModel);
    swap(copy);
    return *this;
}

void FileModel::swap(FileModel &other) {
    std::swap(variable_declarations, other.variable_declarations);
    std::swap(function_declarations, other.function_declarations);
    std::swap(record_declarations, other.record_declarations);
    std::swap(variable_name_by_declaration, other.variable_name_by_declaration);
    std::swap(rvariable_name_by_declaration, other.rvariable_name_by_declaration);
    std::swap(function_name_by_declaration, other.function_name_by_declaration);
    std::swap(rfunction_name_by_declaration, other.rfunction_name_by_declaration);
    std::swap(record_name_by_declaration, other.record_name_by_declaration);
    std::swap(rrecord_name_by_declaration, other.rrecord_name_by_declaration);
    std::swap(headers, other.headers);
    std::swap(last_statement, other.last_statement);
}

std::string FileModel::to_string() {
    SourceUtils::CodeGenerator codeGenerator;
    std::ostringstream out;
    codeGenerator.generate_source_file(*this, out);
    return out.str();
}
