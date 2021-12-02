#include "directory_manager.hpp"

#include <string>

void DirectoryUtils::create_dirs() {
    std::string gen = "mkdir gen";
    std::string libs = "mkdir gen/libs";
    std::string sources = "mkdir gen/sources";
    std::system(gen.c_str());
    std::system(libs.c_str());
    std::system(sources.c_str());
}

void DirectoryUtils::clean_up() {
    std::string clean = "rm -r gen";
    std::system(clean.c_str());
}
