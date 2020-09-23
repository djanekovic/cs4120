#pragma once
#include <string>

#include "position.h"

enum class TokenType {
    Identifier,
    Integer,
    Character,
    String,
    Keyword,
    Symbol,
    Error,
    End
};

struct Token final {
    TokenType const type;
    Position const position;
    std::string const value;
};
