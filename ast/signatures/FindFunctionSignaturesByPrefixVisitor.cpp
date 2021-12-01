#include "FindFunctionSignaturesByPrefixVisitor.hpp"

using namespace ast_tools;

std::string FindFunctionSignaturesByPrefixVisitor::getSignature(const clang::FunctionDecl* D) {
    clang::ASTContext& ctx = D->getASTContext();
    clang::SourceManager& mgr = ctx.getSourceManager();

    clang::SourceRange range = clang::SourceRange(D->getSourceRange().getBegin(),
                                                  D->getBody()->getSourceRange().getBegin());
    llvm::StringRef s = clang::Lexer::getSourceText(clang::CharSourceRange::getTokenRange(range), mgr, ctx.getLangOpts());

    return s.substr(0, s.size() - 2).str().append(";");
}

bool FindFunctionSignaturesByPrefixVisitor::VisitFunctionDecl(clang::FunctionDecl* Declaration) {
    if (Declaration->getName().startswith(prefix_)) {
        clang::FullSourceLoc FullLocation = Context->getFullLoc(Declaration->getBeginLoc());
        if (FullLocation.isValid()) signatures_.push_back(getSignature(Declaration));
    }
    return true;
}
