#pragma once

#include <memory>
#include <sstream>
#include "token.h"

class ParserContext {
    private:
        std::string filename;
        int line;
        int column;
        Token current_token;

    public:
        //TODO: rule of five
        ParserContext(int line, int column): line{line}, column{column} {};
        ParserContext(): ParserContext(1, 0) {};
        ~ParserContext() {}

        void set_token(Token &new_token)
        {
            current_token = new_token;
        }

        //TODO: fmt
        std::string get_value(void)
        {
            std::ostringstream value_stream;
            value_stream << line << ":" << column << " ";
            value_stream << current_token.get_type();

            return value_stream.str();
        }

        void new_line(void) {
            column = 0;
            line++;
        }

        void step(void) {
            column++;
        }
};
