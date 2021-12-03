#include "processing_ast.hpp"
#include "check/DeclarationKind.hpp"
#include "check/CheckDeclarationAction.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

using namespace clang;
using namespace ast_tools;

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

class LoopPrinter : public MatchFinder::MatchCallback {
public :
    virtual void run(const MatchFinder::MatchResult &Result) {
//        std::cout << "begin run" << std::endl;
        if (const VarDecl *FS = Result.Nodes.getNodeAs<clang::VarDecl>("var_decl")) {
            name = FS->getNameAsString();
//            std::cout << "in if" << std::endl;
//            std::cout << "name = " << FS->getNameAsString() << std::endl;
        }
//            FS->dump();
    }

    std::string get_name() {
        return name;
    }

private:
    std::string name;
};

namespace ast_tools {
    std::string GetNameFromSignature(const std::string &signature) {
        std::string not_return_type;
        std::stringstream ss(signature);
        std::getline(ss, not_return_type, ' ');
        std::getline(ss, not_return_type, ' ');

        return not_return_type.substr(0, not_return_type.find_first_of('('));
    }

    std::vector<std::string> GetSignaturesByPrefix(const std::string &code, const std::string &prefix) {
        std::vector<std::string> signatures;
        clang::tooling::runToolOnCode(
                std::make_unique<FindFunctionSignaturesByPrefixAction>(prefix, signatures),
                code
        );

        return signatures;
    }

    std::vector<std::string> GetSignaturesByName(const std::string &code, const std::string &name) {
        auto signatures_by_prefix = GetSignaturesByPrefix(code, name);
        std::vector<std::string> matched_by_name;
        std::copy_if(
                signatures_by_prefix.begin(),
                signatures_by_prefix.end(),
                std::back_inserter(matched_by_name),
                [&name](const std::string &signature) { return GetNameFromSignature(signature) == name; }
        );

        return matched_by_name;
    }

    std::string GetNameByDeclaration(const std::string &declaration) {
        std::string name;
        clang::tooling::runToolOnCode(
                std::make_unique<GetVariableNameByDeclarationAction>(name),
                declaration
        );

        return name;
    }

    DeclarationKind GetDeclarationKind(const std::string &line) {
        DeclarationKind kind;
        clang::tooling::runToolOnCode(
                std::make_unique<CheckDeclarationAction>(kind),
                line
        );
        return kind;
    }

    bool CheckIsVariable(const std::string &line) {
        DeclarationKind kind = GetDeclarationKind(line);
        return kind == VARIABLE;
//        llvm::cl::NumOccurrencesFlag flag = llvm::cl::NumOccurrencesFlag::OneOrMore;
//        std::vector<std::string> Sources;
//        std::system("touch my_source.cc");
//        Sources.push_back("my_source.cc");
//
//        int c = 2;
//        std::system(("echo " + line + " > my_source.cc").c_str());
//        const char **path = new const char *[2]{"REPL-for-cpp", "my_source.cc"};
//        CommonOptionsParser OptionsParser(c, path, MyToolCategory);
//        ClangTool Tool(OptionsParser.getCompilations(), Sources);
//
//        auto ExpectedParser = CommonOptionsParser::create(c, path, MyToolCategory, flag);
//        if (!ExpectedParser) {
//            llvm::errs() << ExpectedParser.takeError();
//        }
    }

    bool CheckIsFunction(const std::string &line) {
        DeclarationKind kind = GetDeclarationKind(line);
        return kind == FUNCTION;
    }

    bool CheckIsClass(const std::string &line) {
        DeclarationKind kind = GetDeclarationKind(line);
        return kind == CLASS;
    }
}
//
//int main() {
//    const std::string code = "class C { void foo(int a) {} void bar() {} }; "
//                             "class A { void meh() {} }; "
//                             "class B { void fee(const int a, const int n) {} };";
//    const std::string prefix = "f";
//    auto signatures = GetSignaturesByPrefix(code, prefix);
//
//    for (const auto& signature: signatures) {
//        std::cout << signature << std::endl;
//    }
//
//    const std::string name = "foo";
//    signatures = GetSignaturesByName(code, name);
//    for (const auto& signature: signatures) {
//        std::cout << signature << std::endl;
//    }
//}