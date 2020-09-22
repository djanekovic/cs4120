#pragma once
#include <array>
#include <memory>
#include <vector>
#include <cstdio>
#include <string_view>

#include "token.h"
#include "position.h"

class Lexer {
    private:
        static constexpr std::array keywords {"if", "else", "while", "return", "length", "int", "bool", "true", "false", "use"};
        Position current_position;
        std::unique_ptr<char[]> file_buffer;
        std::string_view file;

        Token get_digit_token();
        Token get_two_char_token(const std::string& ch);
        Token get_three_char_token(const std::string& ch);
        Token get_character_token();
        Token get_string_token();
        bool is_end() const;
        void skip_comments();
        Token advance();
    public:
        Lexer(const char *filename);
        std::vector<Token> get_tokens();
};
