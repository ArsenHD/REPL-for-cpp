#include "ast_utils.hpp"

#include "../ast/processing_ast.hpp"

AstUtils::ElementType AstUtils::get_element_type() {
    return DECLARATION; // TODO: replace by actual call to AST methods
}

std::vector<std::string> AstUtils::get_function_signatures_by_name(const std::string& source, const std::string &name) {
    return ast_tools::GetSignaturesByName(source, name);//"void " + name + "(int, int)"; // TODO: replace by actual call to AST methods
}

bool AstUtils::is_variable_declaration(const std::string &line) {
//    return ast_tools::CheckIsVariable(line);
    return ast_tools::CheckIsVariable(line); // TODO: replace by actual call to AST methods
}

std::string AstUtils::parse_name(const std::string &declaration) {
    return ast_tools::GetNameByDeclaration(declaration); // TODO: replace by actual call to AST methods
}

