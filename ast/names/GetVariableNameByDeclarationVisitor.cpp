#include "GetVariableNameByDeclarationVisitor.hpp"

using namespace ast_tools;

bool GetVariableNameByDeclarationVisitor::VisitVarDecl(clang::VarDecl* Declaration) {
    name = Declaration->getNameAsString();
    return true;
}

bool GetVariableNameByDeclarationVisitor::VisitFunctionDecl(clang::FunctionDecl *Declaration) {
    name = Declaration->getNameAsString();
    return false;
}

bool GetVariableNameByDeclarationVisitor::VisitCXXRecordDecl(clang::CXXRecordDecl *Declaration) {
    name = Declaration->getNameAsString();
    return false;
}
