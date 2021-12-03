#pragma once

#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTConsumer.h"
#include "GetVariableNameByDeclarationVisitor.hpp"

namespace ast_tools {
    class GetVariableNameByDeclarationVisitor
            : public clang::RecursiveASTVisitor<GetVariableNameByDeclarationVisitor> {
    public:
        explicit GetVariableNameByDeclarationVisitor(
                clang::ASTContext *Context,
                std::string &variable_name
        ) : Context(Context), name(variable_name) {}

        bool VisitVarDecl(clang::VarDecl *Declaration);

        bool VisitFunctionDecl(clang::FunctionDecl *Declaration);

        bool VisitCXXRecordDecl(clang::CXXRecordDecl *Declaration);

    private:
        clang::ASTContext *Context;
        std::string &name;
    };
}