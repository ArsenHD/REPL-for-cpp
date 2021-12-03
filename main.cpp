#include "utils/library_utils.hpp"
#include "utils/code_generator.hpp"
#include "utils/ast_utils.hpp"
#include "utils/directory_manager.hpp"
#include "multiline/code_block.hpp"
#include "flags/flags.hpp"
#include "model/file_model.hpp"
#include "ast/processing_ast.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace ast_tools;

using namespace Options;
using namespace SourceUtils;
using namespace DirectoryUtils;

int main(int argc, char **argv) {

    DirectoryUtils::create_dirs();

    std::string current_line;

    auto file_model = FileModel();
    auto code_generator = CodeGenerator();

    std::unordered_map<std::string, void *> memory_state;

    auto old_model = file_model;

    while (getline(std::cin, current_line)) {
        Options::Flag flag = Options::check_for_flag(current_line);

        switch (flag) {
            case SIGNATURE: {
                std::string name = Options::parse_after_flag(current_line);
                std::string current_source = file_model.to_string();
                std::vector<std::string> signatures = AstUtils::get_function_signatures_by_name(current_source, name);
                break;
            }
            case LOAD: {
                load_header(current_line, file_model);
                break;
            }
            case CREATE_OBJECT: {
                std::string block = CodeBlock::read_block();
                if (CheckIsFunction(block)) {
                    file_model.add_function(block);
                } else if (CheckIsClass(block)) {
                    file_model.add_record(block);
                }
//                file_model.add_code_block(block);
                break;
            }
            case EVAL: {
                std::string expression = Options::parse_after_flag(current_line);
                std::stringstream output;
                output << COUT << " << " << expression << " << " << ENDL << ";";
                file_model.update_last_statement(output.str());
                break;
            }
            case EXIT: {
                DirectoryUtils::clean_up();
                return 0;
            }
            case DEFAULT: {
                if (!AstUtils::is_variable_declaration(current_line)) {
                    file_model.update_last_statement(current_line);
                }
                break;
            }
        }

        if (flag != DEFAULT && flag != EVAL) {
            continue;
        }

        for (auto& declaration : file_model.get_variable_declarations()) {
            std::string variable_name = file_model.get_variable_name_by_declaration(declaration);
            size_t size = LibraryUtils::get_size_of(variable_name);
            void *memory = malloc(size);
            void *so = nullptr;
            void *variable_memory = LibraryUtils::load_variable_by_name(so, variable_name);
            memcpy(memory, variable_memory, size);
            dlclose(so);
            memory_state.insert(std::make_pair(variable_name, memory));
        }

        if (flag == DEFAULT && AstUtils::is_variable_declaration(current_line)) {
            file_model.add_variable_declaration(current_line);
        }

        std::string lib_name = LibraryUtils::get_library_name();
        std::string source_file_name = code_generator.get_source_file_name();

        std::ofstream source_file(source_file_name);

        code_generator.generate_source_file(file_model, source_file);

        source_file.close();

        int code = LibraryUtils::build_library(source_file_name, lib_name);
        if (!code) {
            // now that the new library is built, we assign cached values to the variables
            for (auto &state: memory_state) {
                std::string variable = state.first;
                void *memory = state.second;
                void *so = nullptr;
                void *new_memory = LibraryUtils::load_variable_by_name(so, variable);
                size_t size = LibraryUtils::get_size_of(variable);
                memcpy(new_memory, memory, size);
                dlclose(so);
            }

            LibraryUtils::load_main_function();
        } else {
            file_model = old_model;
        }
        old_model = file_model;
    }

    DirectoryUtils::clean_up();

    return 0;
}
