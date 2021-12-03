#include "FindFunctionSignaturesByPrefixAction.hpp"
#include "FindFunctionSignaturesByPrefixConsumer.hpp"

using namespace ast_tools;

std::unique_ptr<clang::ASTConsumer> FindFunctionSignaturesByPrefixAction::CreateASTConsumer(
        clang::CompilerInstance& Compiler, llvm::StringRef InFile) {
    return std::make_unique<FindFunctionSignaturesByPrefixConsumer>(&Compiler.getASTContext(), prefix_, signatures_);
}
