#include "library_utils.hpp"

std::string LibraryUtils::get_library_name(int id) {
    return "../libs/" + LIB + std::to_string(id) + EXT;
}

void LibraryUtils::build_library(const std::string &source, const std::string &library_name) {
    std::string command = "g++ -fPIC -shared -o " + library_name + " " + source;
    std::system(command.c_str());
}

void LibraryUtils::load_and_run(int id) {
    std::string lib_name = get_library_name(id);
    using func_type = void (*)();
    auto so = dlopen(lib_name.c_str(), RTLD_LAZY);
    auto f = reinterpret_cast<func_type>(dlsym(so, "_Z3foov"));
    f();
    dlclose(so);
}
