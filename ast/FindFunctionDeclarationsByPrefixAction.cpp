#include "FindFunctionDeclarationsByPrefixAction.hpp"
#include "FindFunctionDeclarationsByPrefixConsumer.hpp"

using namespace ast_tools;

std::unique_ptr<clang::ASTConsumer> FindFunctionDeclarationsByPrefixAction::CreateASTConsumer(
        clang::CompilerInstance& Compiler, llvm::StringRef InFile) {
    return std::make_unique<FindFunctionDeclarationsByPrefixConsumer>(&Compiler.getASTContext(), prefix_, signatures_);
}
