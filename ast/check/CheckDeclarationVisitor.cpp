#include "CheckDeclarationVisitor.hpp"
#include <iostream>

using namespace ast_tools;

//bool CheckDeclarationVisitor::VisitDecl(clang::Decl* Declaration) {
//    clang::FullSourceLoc FullLocation = Context->getFullLoc(Declaration->getBeginLoc());
//    if (FullLocation.isValid()) is_declaration_ = true;
//
//    return false;
//}

bool CheckDeclarationVisitor::VisitFunctionDecl(clang::FunctionDecl *Declaration) {
    bool in_main = IsInMainFile(Declaration);
    if (!in_main) {
        Declaration->dump();
        return true;
    }
//    return RecursiveASTVisitor::VisitFunctionDecl(Declaration);
//    std::cout << Declaration->getNameAsString() << std::endl;
    kind = FUNCTION;
    return false;
}

bool CheckDeclarationVisitor::VisitCXXRecordDecl(clang::CXXRecordDecl *Declaration) {
    bool in_main = IsInMainFile(Declaration);
    if (!in_main) {
        return true;
    }
    kind = CLASS;
    return false;
}

bool CheckDeclarationVisitor::VisitVarDecl(clang::VarDecl *Declaration) {
    bool in_main = IsInMainFile(Declaration);
    if (!in_main) {
        return true;
    }
    kind = VARIABLE;
    return false;
}

bool CheckDeclarationVisitor::IsInMainFile(clang::FunctionDecl* Declaration) {
    return Context->getSourceManager().isInMainFile(Declaration->getOuterLocStart());
}
bool CheckDeclarationVisitor::IsInMainFile(clang::CXXRecordDecl* Declaration) {
    return Context->getSourceManager().isInMainFile(Declaration->getOuterLocStart());
}
bool CheckDeclarationVisitor::IsInMainFile(clang::VarDecl* Declaration) {
    return Context->getSourceManager().isInMainFile(Declaration->getOuterLocStart());
}
