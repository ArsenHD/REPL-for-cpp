#include "GetVariableNameByDeclarationAction.hpp"
#include "GetVariableNameByDeclarationConsumer.hpp"

using namespace ast_tools;

std::unique_ptr<clang::ASTConsumer> GetVariableNameByDeclarationAction::CreateASTConsumer(
        clang::CompilerInstance& Compiler, llvm::StringRef InFile) {
    return std::make_unique<GetVariableNameByDeclarationConsumer>(&Compiler.getASTContext(), variable_name);
}
