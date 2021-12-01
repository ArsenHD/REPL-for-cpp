#include "FindFunctionDeclarationsByPrefixConsumer.hpp"

using namespace ast_tools;

void FindFunctionDeclarationsByPrefixConsumer::HandleTranslationUnit(clang::ASTContext& Context) {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
}