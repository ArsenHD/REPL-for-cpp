//
// Created by kirill on 29.11.2021.
//

#include <assert.h>
#include <dlfcn.h>
#include <iostream>
#include <fstream>

static const std::string LIB = "lib";
static const std::string EXT = ".so";

int main(int argc, char **argv) {
    std::string line;
    int id = 0;
    while (std::cin >> line) {
        std::string file_name = LIB + std::to_string(id) + EXT;
        std::cout << file_name << std::endl;
        std::ofstream file(file_name);
        file.open(file_name);
        file << line;
        id++;
        file.close();
    }
    return 0;
}
