#pragma once

#include "../multiline/code_block.hpp"
#include "../model/file_model.hpp"

#include <vector>
#include <string>

namespace SourceUtils {
    class CodeGenerator {
    public:
        std::string get_source_file_name();

        void generate_source_file(FileModel &, std::ostream &) const;

        void print_indent(std::ostream &file, int tabs) const;
    };

    const std::string SOURCE_FILE = "SOURCE";
    const std::string CPP = ".cpp";
    const std::string METHOD_NAME = "__repl_function__";
    const std::string TAB = "    ";
    const std::string COUT = "std::cout";
    const std::string ENDL = "std::endl";
}