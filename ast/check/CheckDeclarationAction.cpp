#include "CheckDeclarationAction.hpp"
#include "CheckDeclarationConsumer.hpp"

using namespace ast_tools;

std::unique_ptr<clang::ASTConsumer> CheckDeclarationAction::CreateASTConsumer(
        clang::CompilerInstance& Compiler, llvm::StringRef InFile) {
    return std::make_unique<CheckDeclarationConsumer>(&Compiler.getASTContext(), kind);
}
