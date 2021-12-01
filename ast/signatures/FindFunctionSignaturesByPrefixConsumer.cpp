#include "FindFunctionSignaturesByPrefixConsumer.hpp"

using namespace ast_tools;

void FindFunctionSignaturesByPrefixConsumer::HandleTranslationUnit(clang::ASTContext& Context) {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
}