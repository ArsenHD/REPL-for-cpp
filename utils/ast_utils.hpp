#pragma once

#include <string>

namespace AstUtils {
    enum ElementType {
        DECLARATION,
        STATEMENT
    };

    ElementType get_element_type();

    std::string get_function_signature_by_name(const std::string&);
}