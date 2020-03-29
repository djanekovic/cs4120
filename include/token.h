#pragma once

#include <string>
#include <sstream>

enum class TokenType {Id, Integer, Character, String, Symbol, Keyword, End, Error};

class Token {
    private:
        TokenType type;
        std::string value;
        int line;
        int column;

    public:
        Token() = default;
        Token(TokenType type, std::string value, int line, int column):
            type {type}, value{value}, line{line}, column{column} {}

        //TODO: fmt
        std::string get_value() {
            std::ostringstream value_stream;
            value_stream << line << ":" << column << " ";
            value_stream << get_type();

            return value_stream.str();
        }

    private:
        std::string get_type() {
            std::string type_str;

            switch(type) {
                case TokenType::Id:
                    type_str += "id ";
                    break;
                case TokenType::Integer:
                    type_str += "integer ";
                    break;
                case TokenType::Character:
                    type_str += "character ";
                    // trim '
                    value.erase(value.begin());
                    value.erase(value.end() - 1);
                    break;
                case TokenType::String:
                    type_str += "string ";
                    // trim "
                    value.erase(value.begin());
                    value.erase(value.end() - 1);
                    break;
                case TokenType::Error:
                    type_str += "error:";
                default:;
            }

            type_str += value;

            return type_str;
        }
};
