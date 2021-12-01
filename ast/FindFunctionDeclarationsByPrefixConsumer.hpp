#pragma once

#include "FindFunctionDeclarationsByPrefixVisitor.hpp"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

namespace ast_tools {
    class FindFunctionDeclarationsByPrefixConsumer : public clang::ASTConsumer {
    public:
        explicit FindFunctionDeclarationsByPrefixConsumer(
                clang::ASTContext* Context,
                std::string prefix,
                std::vector<std::string>& signatures
        ) : Visitor(Context, std::move(prefix), signatures) {}

        void HandleTranslationUnit(clang::ASTContext& Context) override;
    private:
        FindFunctionDeclarationsByPrefixVisitor Visitor;
    };
}
