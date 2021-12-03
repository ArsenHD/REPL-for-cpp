#include "directory_manager.hpp"

#include <string>

void DirectoryUtils::create_dirs() {
    std::string gen = "mkdir gen -p";
    std::string libs = "mkdir gen/libs -p";
    std::string sources = "mkdir gen/sources -p";
    std::system(gen.c_str());
    std::system(libs.c_str());
    std::system(sources.c_str());
}

void DirectoryUtils::clean_up() {
    std::string clean = "rm -r gen";
    std::system(clean.c_str());
}
