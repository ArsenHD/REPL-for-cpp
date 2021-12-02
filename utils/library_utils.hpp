#pragma once

#include <dlfcn.h>
#include <cstdlib>
#include <iostream>

namespace LibraryUtils {
    // TODO: define somewhere else
    const std::string LIB = "lib";
    const std::string EXT = ".so";

    std::string get_library_name(int id);

    int build_library(const std::string &source, const std::string &library_name);

    void load_and_run(int id);
}