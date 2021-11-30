//
// Created by kirill on 29.11.2021.
//

#include <dlfcn.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

static const std::string LIB = "lib";
static const std::string EXT = ".so";

static const std::string SOURCE = "SOURCE";
static const std::string CPP = ".cpp";

static const char *METHOD_NAME = "foo";

static const std::string TAB = "    ";

void print_tabulation(std::ofstream &file, int amount) {
    for (int i = 0; i < amount; i++) {
        file << TAB;
    }
}

std::string get_source_file_name(int id) {
    return SOURCE + std::to_string(id) + CPP;
}

std::string get_library_name(int id) {
    return LIB + std::to_string(id) + EXT;
}

void load_and_run(int id) {
    std::string lib_name = get_library_name(id);
    void *so = dlopen(lib_name.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    auto (*f)() = reinterpret_cast<void (*)()>(dlsym(so, METHOD_NAME));
    f();
}

void generate_source_file(const std::vector <std::string> &lines, std::ofstream &file) {
    // TODO: add header includes to the beginning of the file
    std::string function_header = "void " + SOURCE + "() {";
    file << function_header << std::endl;
    for (const std::string &line : lines) {
        print_tabulation(file, 1);
        file << line;
        file << std::endl;
    }
    file << "}";
    file << std::endl;
}

void build_library(const std::string &source, const std::string &library_name) {
    std::string command = "g++ -fpic -shared -o " + library_name + " " + source;
    std::system(command.c_str());
}

int main(int argc, char **argv) {
    std::string current_line;
    int id = 0;

    std::vector <std::string> lines;

    while (getline(std::cin, current_line)) {
        std::string lib_name = get_library_name(id);
        std::string source_file_name = get_source_file_name(id);

        std::ofstream source_file(source_file_name);

        lines.push_back(current_line);

        generate_source_file(lines, source_file);

        source_file.close();

        build_library(source_file_name, lib_name);
        id++;
    }

    return 0;
}
