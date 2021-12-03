#include "CheckDeclarationConsumer.hpp"

using namespace ast_tools;

void CheckDeclarationConsumer::HandleTranslationUnit(clang::ASTContext& Context) {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
}