#include "ast_utils.hpp"

AstUtils::ElementType AstUtils::get_element_type() {
    return DECLARATION; // TODO: replace by actual call to AST methods
}

std::string AstUtils::get_function_signature_by_name(const std::string &name) {
    return "void " + name + "(int, int)"; // TODO: replace by actual call to AST methods
}

bool AstUtils::is_variable_declaration(const std::string &line) {
    return true; // TODO: replace by actual call to AST methods
}

std::string AstUtils::parse_variable_name(const std::string &declaration) {
    return "a"; // TODO: replace by actual call to AST methods
}

