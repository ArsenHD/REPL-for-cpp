#pragma once

#include "signatures/FindFunctionSignaturesByPrefixAction.hpp"

namespace ast_tools {
    std::vector<std::string> GetSignaturesByPrefix(const std::string& code, const std::string& prefix);

    std::vector<std::string> GetSignaturesByName(const std::string& code, const std::string& name);
}