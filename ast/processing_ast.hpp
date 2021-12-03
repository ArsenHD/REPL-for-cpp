#pragma once

#include "signatures/FindFunctionSignaturesByPrefixAction.hpp"
#include "names/GetVariableNameByDeclarationAction.hpp"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace llvm;


namespace ast_tools {
    std::vector<std::string> GetSignaturesByPrefix(const std::string& code, const std::string& prefix);

    std::vector<std::string> GetSignaturesByName(const std::string& code, const std::string& name);

    std::string GetNameByDeclaration(const std::string& declaration);

    bool CheckIsVariable(const std::string& line);
    bool CheckIsFunction(const std::string& line);
    bool CheckIsClass(const std::string& line);
}