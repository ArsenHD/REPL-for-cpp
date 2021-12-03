#pragma once

#include "GetVariableNameByDeclarationVisitor.hpp"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

namespace ast_tools {
    class GetVariableNameByDeclarationConsumer : public clang::ASTConsumer {
    public:
        explicit GetVariableNameByDeclarationConsumer(
                clang::ASTContext* Context,
                std::string& variable_name
        ) : Visitor(Context, variable_name) {}

        void HandleTranslationUnit(clang::ASTContext& Context) override;
    private:
        GetVariableNameByDeclarationVisitor Visitor;
    };
}
