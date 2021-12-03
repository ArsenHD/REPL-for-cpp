#pragma once

#include "FindFunctionSignaturesByPrefixConsumer.hpp"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

namespace ast_tools {

    class FindFunctionSignaturesByPrefixAction : public clang::ASTFrontendAction {
    public:
        explicit FindFunctionSignaturesByPrefixAction(
                std::string prefix,
                std::vector<std::string>& signatures
        ) : prefix_(std::move(prefix)), signatures_(signatures) {}

        virtual std::unique_ptr<clang::ASTConsumer>
        CreateASTConsumer(clang::CompilerInstance& Compiler, llvm::StringRef InFile);

    private:
        std::string prefix_;
        std::vector<std::string>& signatures_;
    };
}
