#pragma once

#include "CheckDeclarationConsumer.hpp"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

namespace ast_tools {

    class CheckDeclarationAction : public clang::ASTFrontendAction {
    public:
        explicit CheckDeclarationAction(
                DeclarationKind& kind
        ) : kind(kind) {}

        virtual std::unique_ptr<clang::ASTConsumer>
        CreateASTConsumer(clang::CompilerInstance& Compiler, llvm::StringRef InFile);

    private:
        DeclarationKind& kind;
    };
}
