#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
// Declares llvm::cl::extrahelp.
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace llvm;

StatementMatcher variable_declaration_matcher = declStmt(hasSingleDecl(varDecl())).bind("var_decl");

//void foo(const std::string& source) {
//    StatementMatcher variable_declaration_matcher = declStmt(varDecl()).bind("var_decl");
//    variable_declaration_matcher;
//}

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp("\nMore help text...\n");

class LoopPrinter : public MatchFinder::MatchCallback {
public :
    virtual void run(const MatchFinder::MatchResult &Result) {
        if (const VarDecl *FS = Result.Nodes.getNodeAs<clang::VarDecl>("var_decl"))
            FS->dump();
    }
};

int main(int argc, const char **argv) {
    llvm::cl::NumOccurrencesFlag flag = llvm::cl::NumOccurrencesFlag::OneOrMore;


    auto ExpectedParser = CommonOptionsParser::create(argc, argv, MyToolCategory, flag);
    if (!ExpectedParser) {
        // Fail gracefully for unsupported options.
        llvm::errs() << ExpectedParser.takeError();
        return 1;
    }
    CommonOptionsParser& OptionsParser = ExpectedParser.get();
    ClangTool Tool(OptionsParser.getCompilations(),
                   OptionsParser.getSourcePathList());

    LoopPrinter Printer;
    MatchFinder Finder;
    Finder.addMatcher(variable_declaration_matcher, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
}
//
//int main(int argc, const char **argv) {
//    auto ExpectedParser = CommonOptionsParser::create(argc, argv, MyToolCategory);
//    if (!ExpectedParser) {
//        // Fail gracefully for unsupported options.
//        llvm::errs() << ExpectedParser.takeError();
//        return 1;
//    }
//    CommonOptionsParser& OptionsParser = ExpectedParser.get();
//    ClangTool Tool(OptionsParser.getCompilations(),
//                   OptionsParser.getSourcePathList());
//
//    LoopPrinter Printer;
//    MatchFinder Finder;
//    Finder.addMatcher(LoopMatcher, &Printer);
//
//    return Tool.run(newFrontendActionFactory(&Finder).get());
//}