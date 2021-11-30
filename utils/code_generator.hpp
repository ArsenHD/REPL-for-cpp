#pragma once

#include "../multiline/code_block.hpp"
#include "../model/file_model.hpp"

#include <vector>
#include <string>

namespace SourceUtils {
    class CodeGenerator {
    public:
        std::string get_source_file_name(int);

        void generate_source_file(const FileModel &, std::ofstream &) const;

        void print_tabulation(std::ofstream &, int) const;
    };

    const std::string SOURCE_FILE = "SOURCE";
    const std::string CPP = ".cpp";
    const std::string METHOD_NAME = "foo";
    const std::string TAB = "    ";
    const std::string COUT = "std::cout";
    const std::string ENDL = "std::endl";
}