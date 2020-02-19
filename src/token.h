#pragma once

enum class TokenType {Id, Integer, Character, String, Symbol, Keyword, End};

class Token {
    private:
        TokenType type;
        std::string value;

    public:
        Token() = default;
        Token(TokenType type, std::string value): type {type}, value {value} {}

        std::string get_type() {
            std::string type_str;
            switch(type) {
                case TokenType::Id:
                    type_str += "id ";
                    break;
                case TokenType::Integer:
                    type_str += "integer ";
                    break;
                case TokenType::String:
                    type_str += "character ";
                    break;
                default:;
            }

            type_str += value;

            return type_str;
        }
};
