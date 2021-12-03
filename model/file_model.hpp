#pragma once

#include "../multiline/code_block.hpp"

#include <vector>
#include <unordered_set>
#include <string>
#include <unordered_map>

class FileModel {
public:
    FileModel() = default;

    ~FileModel() = default;

    FileModel(const FileModel &fileModel) :
            headers(fileModel.get_headers()),
            function_declarations(fileModel.function_declarations),
            record_declarations(fileModel.record_declarations),
            variable_declarations(fileModel.variable_declarations),
            variable_name_by_declaration(fileModel.variable_name_by_declaration),
            rvariable_name_by_declaration(fileModel.rvariable_name_by_declaration),
            function_name_by_declaration(fileModel.function_name_by_declaration),
            rfunction_name_by_declaration(fileModel.rfunction_name_by_declaration),
            record_name_by_declaration(fileModel.record_name_by_declaration),
            rrecord_name_by_declaration(fileModel.rrecord_name_by_declaration),
//            code_blocks(fileModel.get_code_blocks()),
            last_statement(fileModel.get_last_statement()) {}

    FileModel& operator=(const FileModel& fileModel);

    void add_header(const std::string &);

    void add_function(const std::string&);
    void add_record(const std::string&);
//    void add_code_block(const CodeBlock &);

    void add_variable_declaration(const std::string &);

    void update_last_statement(const std::string &);

    std::string get_variable_name_by_declaration(const std::string&);

    [[nodiscard]] const std::vector<std::string> &get_headers() const;

//    [[nodiscard]] const std::vector<CodeBlock> &get_code_blocks() const;

    [[nodiscard]] const std::unordered_set<std::string> &get_variable_declarations() const;
    [[nodiscard]] const std::unordered_set<std::string> &get_function_declarations() const;
    [[nodiscard]] const std::unordered_set<std::string> &get_record_declarations() const;

    [[nodiscard]] const std::string &get_last_statement() const;

    std::string to_string();


private:
    std::vector<std::string> headers;
//    std::vector<CodeBlock> code_blocks;
    std::unordered_set<std::string> function_declarations;
    std::unordered_set<std::string> record_declarations;
    std::unordered_set<std::string> variable_declarations;
    // variable names
    std::unordered_map<std::string, std::string> variable_name_by_declaration;
    std::unordered_map<std::string, std::string> rvariable_name_by_declaration;
    std::unordered_map<std::string, std::string> function_name_by_declaration;
    std::unordered_map<std::string, std::string> rfunction_name_by_declaration;
    std::unordered_map<std::string, std::string> record_name_by_declaration;
    std::unordered_map<std::string, std::string> rrecord_name_by_declaration;
    std::string last_statement;

    void swap(FileModel&);
};
