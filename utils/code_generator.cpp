#include "code_generator.hpp"
#include <algorithm>

std::string SourceUtils::CodeGenerator::get_source_file_name() {
    return "gen/sources/" + SOURCE_FILE + CPP;
}

void SourceUtils::CodeGenerator::generate_source_file(FileModel &file_model, std::ofstream &file) const {
    std::vector<std::string> headers = file_model.get_headers();
    const std::string cstdio_header = "#include <cstdio>";
    if (find(headers.begin(), headers.end(), cstdio_header) == headers.end()) {
        file << cstdio_header << std::endl;
    }
    for (const std::string &header: headers) {
        file << header << std::endl;
    }
    file << std::endl << std::endl;

    for (const std::string &declaration: file_model.get_variable_declarations()) {
        std::string variable = file_model.get_variable_name_by_declaration(declaration);

        file << "extern \"C\" {" << std::endl;
        print_indent(file, 1);
        file << declaration << std::endl;
        file << "}" << std::endl;
        file << std::endl << std::endl;

        file << "size_t __size_of_" << variable << "() {" << std::endl;
        print_indent(file, 1);
        file << "return sizeof(" << variable << ");" << std::endl;
        file << "}" << std::endl << std::endl;
    }

    // TODO: for now we assume that code blocks can be only function/class/struct declarations
    for (const CodeBlock &block: file_model.get_code_blocks()) {
        block.write_to(file);
    }

    std::string function_header = "void " + METHOD_NAME + "() {";
    file << function_header << std::endl;

    print_indent(file, 1);
    file << file_model.get_last_statement();

    file << "}";
    file << std::endl;
}

void SourceUtils::CodeGenerator::print_indent(std::ofstream &file, int tabs) const {
    for (int i = 0; i < tabs; i++) {
        file << TAB;
    }
}
