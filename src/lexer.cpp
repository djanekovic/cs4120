#include <cassert>
#include <cstdio>
#include <memory>
#include <algorithm>

#include "lexer.h"


Lexer::Lexer(const char *filename)
{
    std::unique_ptr<FILE, decltype(&std::fclose)> file_ptr(std::fopen(filename, "r"), &std::fclose);
    assert(file_ptr.get());

    std::fseek(file_ptr.get(), 0, SEEK_END);
    long filesize = std::ftell(file_ptr.get());
    std::fseek(file_ptr.get(), 0, SEEK_SET);

    file_buffer = std::make_unique<char[]>(filesize);

    assert(std::fread(file_buffer.get(), filesize, 1, file_ptr.get()) == 1);

    file = {file_buffer.get(), static_cast<size_t>(filesize)};
}


Token Lexer::get_digit_token()
{
    Position start_position = current_position;
    std::string number;

    for (;;) {
        auto ch = file[current_position.idx];
        if (isdigit(ch)) {
            number.push_back(ch);
            current_position.advance();
        } else {
            break;
        }
    }

    return Token(TokenType::Integer, start_position, number);
}


Token Lexer::get_two_char_token(const std::string& ch)
{
    Position start_position = current_position;

    current_position.advance();
    if (file.size() > current_position.idx) {
        if (file[current_position.idx] == '=') {
            current_position.advance();
            return Token(TokenType::Symbol, start_position, ch + '=');
        }
    }

    return Token(TokenType::Symbol, start_position, ch);
}


Token Lexer::get_three_char_token(const std::string& ch)
{
    Position start_position = current_position;

    current_position.advance();
    if (file.size() > current_position.idx+1) {
        if (file[current_position.idx] == '>' && file[current_position.idx + 1] == '>') {
            current_position.advance();
            current_position.advance();
            return Token(TokenType::Symbol, start_position, ch + ">>");
        }
    }

    return Token(TokenType::Symbol, start_position, ch);
}

Token Lexer::get_character_token()
{
    char ch;
    Position start_position = current_position;

    current_position.advance();
    if (file.size() > current_position.idx + 1) {
        ch = file[current_position.idx];
        if (isalpha(ch) && file[current_position.idx + 1] == '\'') {
            current_position.advance();
            current_position.advance();
            return Token(TokenType::Character, start_position, std::string(1, ch));
        }
    }

    return Token(TokenType::Error, start_position, "empty character literal");
}

Token Lexer::get_string_token()
{
    Position start_position = current_position;
    std::string string;

    current_position.advance();

    for(;;) {
        auto ch = file[current_position.idx];

        if (ch == '"') {
            current_position.advance();
            break;
        } else {
            string += ch;
            current_position.advance();
        }
    }

    return Token(TokenType::String, start_position, string);
}


bool Lexer::is_end() const
{
    return file.size() == current_position.idx;
}


void Lexer::skip_comments()
{
    while(file.size() > current_position.idx+1) {
        if (file[current_position.idx] == '/' && file[current_position.idx+1] == '/') {
            current_position.advance();
            current_position.advance();

            for(;;) {
                if (file[current_position.idx] == '\n') {
                    current_position.newline();
                    break;
                } else if (file.size() == current_position.idx-1) {
                    return;
                }
                current_position.advance();
            }
        } else {
            return;
        }
    }
}


Token Lexer::advance()
{
    while(isspace(file[current_position.idx])) {
        switch(file[current_position.idx]) {
            case ' ':
            case '\t':
            case '\r':
                current_position.advance();
                break;
            case '\n':
                current_position.newline();
                break;
        }

        if (is_end()) {
            return Token(TokenType::End);
        }
    }

    skip_comments();

    if (is_end()) {
        return Token(TokenType::End);
    }

    Position start_position = current_position;

    auto ch = file[current_position.idx];
    switch(ch) {
        case '(':
        case '{':
        case '}':
        case ')':
        case '[':
        case ']':
        case '-':
        case '/':
        case '%':
        case '+':
        case '&':
        case '|':
        case ':':
        case ',':
        case ';':
        case '_':
            current_position.advance();
            return Token(TokenType::Symbol, start_position, std::string(1, ch));
        case '!':
        case '<':
        case '>':
        case '=':
            return get_two_char_token(std::string(1, ch));
        case '*':
            return get_three_char_token(std::string(1, ch));
        case '\'':
            return get_character_token();
        case '"':
            return get_string_token();
    }

    if (isdigit(ch)) {
        return get_digit_token();
    }

    if (isalpha(ch)) {
        std::string name;

        for(;;) {
            if (is_end()) {
                return Token(TokenType::End);
            }

            auto ch = file[current_position.idx];
            if (isalnum(ch) || ch == '\'' ||  ch == '_') {
                name += ch;
                current_position.advance();
            } else {
                break;
            }
        }

        if (std::find(std::begin(keywords), std::end(keywords), name) != std::end(keywords)) {
            return Token(TokenType::Keyword, start_position, name);
        }
        return Token(TokenType::Identifier, start_position, name);
    }

    return Token(TokenType::Error, start_position, "Unknown token");
}


std::vector<Token> Lexer::get_tokens()
{
    std::vector<Token> tokens;

    for (;;) {
        Token t = Lexer::advance();
        tokens.emplace_back(t);

        if (t.type == TokenType::End || t.type == TokenType::Error) {
            break;
        }
    }

    return tokens;
}
