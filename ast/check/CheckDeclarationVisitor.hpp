#pragma once

#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTConsumer.h"
#include "CheckDeclarationVisitor.hpp"
#include "DeclarationKind.hpp"

namespace ast_tools {
    class CheckDeclarationVisitor
            : public clang::RecursiveASTVisitor<CheckDeclarationVisitor> {
    public:
        explicit CheckDeclarationVisitor(
                clang::ASTContext* Context,
                DeclarationKind& kind
        ) : kind(kind), Context(Context) {}

        bool VisitFunctionDecl(clang::FunctionDecl* Declaration);
        // struct/union/class
        bool VisitCXXRecordDecl(clang::CXXRecordDecl* Declaration);
        bool VisitVarDecl(clang::VarDecl* Declaration);
    private:
        clang::ASTContext* Context;
//        std::string& kind
        DeclarationKind& kind = other;
        DeclarationKind other = OTHER;

        bool IsInMainFile(clang::FunctionDecl* Declaration);
        bool IsInMainFile(clang::CXXRecordDecl* Declaration);
        bool IsInMainFile(clang::VarDecl* Declaration);
    };
}