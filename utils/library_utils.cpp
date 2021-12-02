#include "library_utils.hpp"

const std::string cxx =
#ifdef __clang__
        "clang++";
#else
        "g++";
#endif

std::string LibraryUtils::get_library_name(int id) {
    return "gen/libs/" + LIB + std::to_string(id) + EXT;
}

int LibraryUtils::build_library(const std::string &source, const std::string &library_new) {
    std::string command = cxx + " -fPIC -shared -o " + library_new + " " + source;
    int out = std::system(command.c_str());
    return out;
}

void LibraryUtils::load_and_run(int id) {
    std::string lib_name = get_library_name(id);
    using func_type = void (*)();
    auto so = dlopen(lib_name.c_str(), RTLD_LAZY);
    auto f = reinterpret_cast<func_type>(dlsym(so, "_Z3foov"));
    f();
    dlclose(so);
}
