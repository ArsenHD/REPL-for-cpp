#pragma once

#include <string>
#include <vector>

namespace AstUtils {
    enum ElementType {
        DECLARATION,
        STATEMENT
    };

    ElementType get_element_type();

    std::vector<std::string> get_function_signatures_by_name(const std::string&, const std::string&);

    bool is_variable_declaration(const std::string&);

    std::string parse_name(const std::string &declaration);
}