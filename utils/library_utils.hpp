#pragma once

#include <dlfcn.h>
#include <cstdlib>
#include <iostream>

namespace LibraryUtils {
    // TODO: define somewhere else
    const std::string LIB = "lib";
    const std::string EXT = ".so";

    std::string get_library_name();

    int build_library(const std::string &, const std::string &);

    void load_main_function();

    void *load_variable_by_name(const std::string &);

    size_t get_size_of(const std::string &variable_name);
}