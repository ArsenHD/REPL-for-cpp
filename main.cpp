//
// Created by kirill on 29.11.2021.
//

#include <dlfcn.h>
#include <iostream>
#include <fstream>

static const std::string LIB = "lib";
static const std::string EXT = ".so";

std::string get_lib_name(int id) {
    return LIB + std::to_string(id) + EXT;
}

void load_and_run(int id) {
    std::string lib_name = get_lib_name(id);
    void *so = dlopen(lib_name.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    auto (*f)() = reinterpret_cast<void (*)()>(dlsym(so, lib_name.c_str()));
    f();
}

int main(int argc, char **argv) {
    std::string line;
    int id = 0;
    while (std::cin >> line) {
        std::string lib_name = get_lib_name(id);
        std::cout << lib_name << std::endl;
        std::ofstream file(lib_name);
        file.open(lib_name);
        file << line;
        id++;
        file.close();
    }
    return 0;
}
