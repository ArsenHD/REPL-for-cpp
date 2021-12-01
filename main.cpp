#include "flags/flags.hpp"
#include "multiline/codeblock.hpp"

#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

const std::string LIB = "lib";
const std::string EXT = ".so";

const std::string SOURCE_FILE = "SOURCE";
const std::string CPP = ".cpp";

const std::string METHOD_NAME = "foo";

const std::string TAB = "    ";

void print_tabulation(std::ofstream &file, int amount) {
    for (int i = 0; i < amount; i++) {
        file << TAB;
    }
}

std::string get_source_file_name(int id) {
    return "../sources/" + SOURCE_FILE + std::to_string(id) + CPP;
}

std::string get_library_name(int id) {
    return "../libs/" + LIB + std::to_string(id) + EXT;
}

void load_and_run(int id) {
    std::string lib_name = get_library_name(id);
    using func_type = void (*)();
    auto so = dlopen(lib_name.c_str(), RTLD_LAZY);
    auto f = reinterpret_cast<func_type>(dlsym(so, "_Z3foov"));
    f();
    dlclose(so);
}

void generate_source_file(const std::vector<std::string> &includes,
                          const std::vector<CodeBlock> &blocks,
                          const std::vector<std::string> &lines,
                          std::ofstream &file) {
    for (const std::string& s : includes){
        file << s << std::endl;
    }
    file << std::endl;
    for (CodeBlock block : blocks){
        block.add_to_file(file);
    }
    std::string function_header = "void " + METHOD_NAME + "() {";
    file << function_header << std::endl;
    for (const std::string &line: lines) {
        print_tabulation(file, 1);
        file << line;
        file << std::endl;
    }
    file << "}";
    file << std::endl;
}

void build_library(const std::string &source, const std::string &library_name) {
    std::string command = "g++ -fPIC -shared -o " + library_name + " " + source;
    std::system(command.c_str());
}

int main(int argc, char **argv) {
    std::string current_line;
    int id = 0;

    std::vector<std::string> lines;
    std::vector<std::string> includes;
    std::vector<CodeBlock> blocks;

    while (getline(std::cin, current_line)) {

        FLAG f = check_for_flag(current_line);

        switch (f) {
            case SIGNATURE:
                break; // TODO
            case LOAD:
                load(current_line, includes);
                break;
            case CREATE_OBJECT:{
                CodeBlock block = CodeBlock::create_block();
                blocks.push_back(block);
                break;
            }
            case EXIT:
                return 0;
            case DEFAULT:
                lines.push_back(current_line);
                break;
        }

        std::string lib_name = get_library_name(id);
        std::string source_file_name = get_source_file_name(id);

        std::ofstream source_file(source_file_name);

        generate_source_file(includes, blocks, lines, source_file);

        source_file.close();

        build_library(source_file_name, lib_name);

        load_and_run(id);
        id++;
    }

    return 0;
}
