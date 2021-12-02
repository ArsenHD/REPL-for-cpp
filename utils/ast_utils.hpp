#pragma once

#include <string>

namespace AstUtils {
    enum ElementType {
        DECLARATION,
        STATEMENT
    };

    ElementType get_element_type();

    std::string get_function_signature_by_name(const std::string&);

    bool is_variable_declaration(const std::string&);

    std::string parse_variable_name(const std::string&);
}