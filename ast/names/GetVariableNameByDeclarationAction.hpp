#pragma once

#include "GetVariableNameByDeclarationConsumer.hpp"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"

namespace ast_tools {

    class GetVariableNameByDeclarationAction : public clang::ASTFrontendAction {
    public:
        explicit GetVariableNameByDeclarationAction(std::string &variable_name) : variable_name(variable_name) {};

        virtual std::unique_ptr<clang::ASTConsumer>
        CreateASTConsumer(clang::CompilerInstance &Compiler, llvm::StringRef InFile);

        std::string &variable_name;
    };
}
