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

struct Token {
    TokenType type;
    Position position;
    std::string value;

    Token(TokenType type, Position position, std::string value):
        type{type}, position{position}, value{value} {};
    Token(TokenType type): type{type} {}
};
