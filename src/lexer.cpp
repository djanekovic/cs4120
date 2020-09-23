#include <cassert>
#include <cstdio>
#include <memory>
#include <algorithm>

#include "lexer.h"

//TODO: Lexer could and should be implemented by using only fgetc.
//One should generate FSM, traverse it and generate tokens when end state for some token is
//reached. Using fgetc is not a small change but it should be done.
//
//One could implement peek something like this:
//int peek(FILE *stream) { return std::ungetc(std::fgetc(stream), stream); }

Lexer::Lexer(const char *filename)
{
    std::unique_ptr<FILE, decltype(&std::fclose)> file_descriptor(std::fopen(filename, "r"), &std::fclose);
    assert(file_descriptor.get());

    //TODO: use fstat to get size of file
    std::fseek(file_descriptor.get(), 0, SEEK_END);
    long filesize = std::ftell(file_descriptor.get());
    std::fseek(file_descriptor.get(), 0, SEEK_SET);

    // allocate buffer that we will pass to the string_view
    file_buffer = std::make_unique<char[]>(filesize);

    // read file content in buffer and view that buffer with string_view
    // NOTE: we are using string_view but we are really not using anything from string_view
    // object except size()....
    assert(std::fread(file_buffer.get(), filesize, 1, file_descriptor.get()) == 1);
    file = std::string_view{file_buffer.get(), static_cast<size_t>(filesize)};
}


/**
 * Parse digit token: [0-9]+
 */
Token Lexer::get_digit_token()
{
    const Position start_position = current_position;
    std::string number;

    for (;;) {
        const auto ch = file[current_position.idx];
        if (isdigit(ch)) {
            number.push_back(ch);
            current_position.advance();
        } else {
            break;
        }
    }

    return {TokenType::Integer, start_position, number};
}


/**
 * Check if ch + '=' combinaton is available. If yes, return it else return just ch Token.
 * NOTE: in case more dual character Tokens one could create template parameter for second ch.
 */
Token Lexer::get_two_char_token(const std::string& ch)
{
    const Position start_position = current_position;

    current_position.advance();
    if (file.size() > current_position.idx) {
        if (file[current_position.idx] == '=') {
            current_position.advance();
            return {TokenType::Symbol, start_position, ch + '='};
        }
    }

    return {TokenType::Symbol, start_position, ch};
}


/**
 * Check if ch + '>' + '>' is available. If yes, return it else return just ch Token.
 */
Token Lexer::get_three_char_token(const std::string& ch)
{
    const Position start_position = current_position;

    current_position.advance();
    if (file.size() > current_position.idx+1) {
        if (file[current_position.idx] == '>' && file[current_position.idx + 1] == '>') {
            current_position.advance();
            current_position.advance();
            return {TokenType::Symbol, start_position, ch + ">>"};
        }
    }

    return {TokenType::Symbol, start_position, ch};
}

/**
 * Parse: '[a-zA-Z]' and return error Token if not
 */
Token Lexer::get_character_token()
{
    const Position start_position = current_position;

    current_position.advance();
    if (file.size() > current_position.idx + 1) {
        const auto ch = file[current_position.idx];
        if (isalpha(ch) && file[current_position.idx + 1] == '\'') {
            current_position.advance();
            current_position.advance();
            return {TokenType::Character, start_position, std::string(1, ch)};
        }
    }

    return {TokenType::Error, start_position, "empty character literal"};
}


/**
 * Parse: ".*"
 */
Token Lexer::get_string_token()
{
    const Position start_position = current_position;
    std::string string;

    current_position.advance();

    for(;;) {
        const auto ch = file[current_position.idx];

        if (ch == '"') {
            current_position.advance();
            break;
        } else {
            string += ch;
            current_position.advance();
        }
    }

    return {TokenType::String, start_position, string};
}


/**
 * If next read will return EOF and fail or not.
 */
bool Lexer::is_end() const
{
    return file.size() == current_position.idx;
}


/**
 * Skip lines that start with //
 */
void Lexer::skip_comments()
{
    while(file.size() > current_position.idx+1) {
        if (file[current_position.idx] == '/' && file[current_position.idx+1] == '/') {
            current_position.advance();
            current_position.advance();

            // if we read \n test if next line is also commented
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

/**
 * Get next token.
 *
 * Last token is either TokenType::Error or TokenType::EOF.
 */
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
            return {TokenType::End, {0, 0}, 0};
        }
    }

    skip_comments();

    if (is_end()) {
        return {TokenType::End, {0, 0}, 0};
    }

    const Position start_position = current_position;

    const auto ch = file[current_position.idx];
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
            return {TokenType::Symbol, start_position, std::string(1, ch)};
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
                return {TokenType::End, {0, 0}, 0};
            }

            auto ch = file[current_position.idx];
            if (isalnum(ch) || ch == '\'' ||  ch == '_') {
                name += ch;
                current_position.advance();
            } else {
                break;
            }
        }

        // try to see if name is keyword, if not it is identifier
        if (std::find(std::begin(keywords), std::end(keywords), name) != std::end(keywords)) {
            return {TokenType::Keyword, start_position, name};
        }
        return {TokenType::Identifier, start_position, name};
    }

    return {TokenType::Error, start_position, "Unknown token"};
}


/**
 * Get vector of all the tokens
 */
std::vector<Token> Lexer::get_tokens()
{
    std::vector<Token> tokens;

    for (;;) {
        const Token t = Lexer::advance();
        tokens.emplace_back(t);

        if (t.type == TokenType::End || t.type == TokenType::Error) {
            break;
        }
    }

    return tokens;
}
