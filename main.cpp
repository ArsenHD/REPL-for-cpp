#include "utils/library_utils.hpp"
#include "utils/code_generator.hpp"
#include "utils/ast_utils.hpp"
#include "utils/directory_manager.hpp"
#include "multiline/code_block.hpp"
#include "flags/flags.hpp"
#include "model/file_model.hpp"
#include "ast/processing_ast.hpp"

#include <iostream>
#include <sstream>

using namespace ast_tools;

using namespace Options;
using namespace SourceUtils;
using namespace DirectoryUtils;

int main(int argc, char **argv) {

    DirectoryUtils::create_dirs();

    std::string current_line;
    int id = 0;

    auto file_model = FileModel();
    auto code_generator = CodeGenerator();

    auto old_model = file_model;

    while (getline(std::cin, current_line)) {

        Options::Flag flag = Options::check_for_flag(current_line);

        switch (flag) {
            case SIGNATURE: {
                std::string name = Options::parse_after_flag(current_line);
                std::string signature = AstUtils::get_function_signature_by_name(name);
                break;
            }
            case LOAD:
                load_header(current_line, file_model);
                break;
            case CREATE_OBJECT: {
                CodeBlock block = CodeBlock::read_block();
                file_model.add_code_block(block);
                break;
            }
            case EVAL: {
                std::string expression = Options::parse_after_flag(current_line);
                std::stringstream output;
                output << COUT << " << " << expression << " << " << ENDL << ";";
                file_model.update_last_statement(output.str());
                break;
            }
            case EXIT:
                DirectoryUtils::clean_up();
                return 0;
            case DEFAULT:
                // TODO: if node declaration then:
                file_model.update_last_statement(current_line);
                break;
        }

        std::string lib_name = LibraryUtils::get_library_name(id);
        std::string source_file_name = code_generator.get_source_file_name(id);

        std::ofstream source_file(source_file_name);

        code_generator.generate_source_file(file_model, source_file);

        source_file.close();

        int code = LibraryUtils::build_library(source_file_name, lib_name);
        if (!code) {
            LibraryUtils::load_and_run(id);
        } else {
            id--;
            file_model = old_model;
        }
        old_model = file_model;
        id++;
    }

    DirectoryUtils::clean_up();

    return 0;
}
