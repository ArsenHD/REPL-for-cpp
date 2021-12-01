cmake_minimum_required(VERSION 3.8)

project(REPL-for-cpp)

set(CMAKE_CXX_STANDARD 17)

#if (MSVC)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
#else ()
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20
#    -Wall -Wextra -Werror -Wextra-semi -Wno-self-assign-overloaded -Wno-self-assign-overloaded -Wvla-extension \
#    -g -v -O0
#    -fsanitize=address -fno-omit-frame-pointer -fno-operator-names")
#endif ()
set(LLVM_LINK_COMPONENTS Support)

# Find CMake file for Clang
find_package(Clang REQUIRED)

# Add path to LLVM modules
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${LLVM_CMAKE_DIR}"
        )

# import LLVM CMake functions
include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})

add_llvm_executable(ast_processing
        ast/processing_ast.cpp
        ast/signatures/FindFunctionSignaturesByPrefixVisitor.cpp
        ast/signatures/FindFunctionSignaturesByPrefixConsumer.cpp
        ast/signatures/FindFunctionSignaturesByPrefixAction.cpp
        )
target_link_libraries(ast_processing
        PRIVATE
        clangAST
        clangBasic
        clangFrontend
        clangSerialization
        clangTooling
        )

#add_executable()