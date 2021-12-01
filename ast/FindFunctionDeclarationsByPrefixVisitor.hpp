#pragma once

#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/ASTConsumer.h"
#include "FindFunctionDeclarationsByPrefixVisitor.hpp"

namespace ast_tools {
    class FindFunctionDeclarationsByPrefixVisitor
            : public clang::RecursiveASTVisitor<FindFunctionDeclarationsByPrefixVisitor> {
    public:
        explicit FindFunctionDeclarationsByPrefixVisitor(
                clang::ASTContext* Context,
                std::string prefix,
                std::vector<std::string>& signatures
        ) : prefix_(std::move(prefix)), signatures_(signatures), Context(Context) {}

        bool VisitFunctionDecl(clang::FunctionDecl* Declaration);

        static std::string getDeclaration(const clang::FunctionDecl* D);
    private:
        clang::ASTContext* Context;
        std::string prefix_;
        std::vector<std::string>& signatures_;
    };
}