#include "processing_ast.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

using namespace clang;
using namespace ast_tools;

namespace ast_tools {
    std::string GetNameFromSignature(const std::string& signature) {
        std::string not_return_type;
        std::stringstream ss(signature);
        std::getline(ss, not_return_type, ' ');
        std::getline(ss, not_return_type, ' ');

        return not_return_type.substr(0, not_return_type.find_first_of('('));
    }

    std::vector<std::string> GetSignaturesByPrefix(const std::string& code, const std::string& prefix) {
        std::vector<std::string> signatures;
        clang::tooling::runToolOnCode(
                std::make_unique<FindFunctionSignaturesByPrefixAction>(prefix, signatures),
                code
        );

        return signatures;
    }

    std::vector<std::string> GetSignaturesByName(const std::string& code, const std::string& name) {
        auto signatures_by_prefix = GetSignaturesByPrefix(code, name);
        std::vector<std::string> matched_by_name;
        std::copy_if(
                signatures_by_prefix.begin(),
                signatures_by_prefix.end(),
                std::back_inserter(matched_by_name),
                [&name](const std::string& signature) { return GetNameFromSignature(signature) == name; }
        );

        return matched_by_name;
    }
}

int main() {
    const std::string code = "class C { void foo(int a) {} void bar() {} }; "
                             "class A { void meh() {} }; "
                             "class B { void fee(const int a, const int n) {} };";
    const std::string prefix = "f";
    auto signatures = GetSignaturesByPrefix(code, prefix);

    for (const auto& signature: signatures) {
        std::cout << signature << std::endl;
    }

    const std::string name = "foo";
    signatures = GetSignaturesByName(code, name);
    for (const auto& signature: signatures) {
        std::cout << signature << std::endl;
    }
}