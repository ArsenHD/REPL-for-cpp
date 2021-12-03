#include <sstream>
#include "library_utils.hpp"

const std::string CXX =
#ifdef __clang__
        "clang++";
#else
        "g++";
#endif

std::string LibraryUtils::get_library_name() {
    return "gen/libs/" + LIB + EXT;
}

int LibraryUtils::build_library(const std::string &source, const std::string &library_new) {
    std::string command = CXX + " -fPIC -shared -o " + library_new + " " + source;
    int out = std::system(command.c_str());
    return out;
}

void LibraryUtils::load_main_function() {
    std::string lib_name = get_library_name();
    using func_type = void (*)();
    auto so = dlopen(lib_name.c_str(), RTLD_LAZY);
    auto f = reinterpret_cast<func_type>(dlsym(so, "_Z17__repl_function__v"));
    f();
    dlclose(so);
}

void *LibraryUtils::load_variable_by_name(void *&so, const std::string &name) {
    std::string lib_name = get_library_name();
    so = dlopen(lib_name.c_str(), RTLD_LAZY);
//    std::cout << "lib: " << lib_name << std::endl;
//    std::cout << "variable: " << name << std::endl;
    void *variable = dlsym(so, name.c_str());
    return variable;
}

//size_t LibraryUtils::

size_t LibraryUtils::get_size_of(const std::string &variable_name) {
    std::string name_length = std::to_string(variable_name.length() + 10);
    std::stringstream function_name_builder;
    function_name_builder << "_Z" << name_length << "__size_of_" << variable_name << "v";
    std::string function_name = function_name_builder.str();
//    std::cout << "sizeof function" << function_name << std::endl;

    std::string lib_name = get_library_name();
//    std::cout << "lib_name =" << lib_name << std::endl;
    auto so = dlopen(lib_name.c_str(), RTLD_LAZY);
    using func_t = size_t(*)();
    auto sizeof_func = reinterpret_cast<func_t>(dlsym(so, function_name.c_str()));
    size_t size = sizeof_func();
    dlclose(so);
    return size;
}
