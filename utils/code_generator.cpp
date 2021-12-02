#include "code_generator.hpp"

std::string SourceUtils::CodeGenerator::get_source_file_name(int id) {
    return "../cmake-build-debug/gen/sources/" + SOURCE_FILE + std::to_string(id) + CPP;
}

void SourceUtils::CodeGenerator::generate_source_file(const FileModel &file_model, std::ofstream &file) const {
    for (const std::string &header: file_model.get_headers()) {
        file << header << std::endl;
    }
    file << std::endl;

    // TODO: for now we assume that code blocks can be only function/class/struct declarations
    for (const CodeBlock &block: file_model.get_code_blocks()) {
        block.write_to(file);
    }

    std::string function_header = "void " + METHOD_NAME + "() {";
    file << function_header << std::endl;

    print_tabulation(file, 1);
    file << file_model.get_last_statement();

    file << "}";
    file << std::endl;
}

void SourceUtils::CodeGenerator::print_tabulation(std::ofstream &file, int amount) const {
    for (int i = 0; i < amount; i++) {
        file << TAB;
    }
}
