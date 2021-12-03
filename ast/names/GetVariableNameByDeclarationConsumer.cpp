#include "GetVariableNameByDeclarationConsumer.hpp"

using namespace ast_tools;

void GetVariableNameByDeclarationConsumer::HandleTranslationUnit(clang::ASTContext& Context) {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
}