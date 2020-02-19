#pragma once

#include <vector>
#include <string>
#include "xi_lexer.h"

class XIDriver {
    private:
        XILexer lexer;
        ParserContext ctx;
    public:
        XIDriver() = default;

        void trace_scanning(const std::vector<std::string> &filenames);
};
