#pragma once

#include "CheckDeclarationVisitor.hpp"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

namespace ast_tools {
    class CheckDeclarationConsumer : public clang::ASTConsumer {
    public:
        explicit CheckDeclarationConsumer(
                clang::ASTContext* Context,
                DeclarationKind& kind
        ) : Visitor(Context, kind) {}

        void HandleTranslationUnit(clang::ASTContext& Context) override;
    private:
        CheckDeclarationVisitor Visitor;
    };
}
