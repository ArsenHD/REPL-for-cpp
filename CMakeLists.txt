cmake_minimum_required (VERSION 3.8)

project(REPL-for-cpp)
add_subdirectory(ast)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_C_FLAGS  -stdlib=libc)
#set(CMAKE_CXX_FLAGS -stdlib=libc++)

#set(CMAKE_INCLUDE_PATH /usr/lib/clang/10/include)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 \
#    -Wall -Wextra -Werror -Wextra-semi -Wno-self-assign-overloaded -Wno-self-assign-overloaded -Wvla-extension \
#    -g -v -O0 \
#    -fsanitize=address -fno-omit-frame-pointer -fno-operator-names")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -L./libs -Wl,-rpath=./libs")

set(LLVM_LINK_COMPONENTS Support)

# Find CMake file for Clang
find_package(Clang REQUIRED)

# Add path to LLVM modules
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${LLVM_CMAKE_DIR}"
        )

include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})

add_executable(REPL-for-cpp main.cpp
        utils/library_utils.cpp
        utils/code_generator.cpp
        utils/ast_utils.cpp
        utils/directory_manager.cpp
        flags/flags.cpp multiline/code_block.cpp
        model/file_model.cpp
        )

target_link_libraries(REPL-for-cpp dl ast_processing)
