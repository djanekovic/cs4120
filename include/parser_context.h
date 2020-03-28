#pragma once

#include <memory>
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

        std::string get_value(void)
        {
            return current_token.get_value();
        }

        void new_line(void) {
            column = 0;
            line++;
        }

        void step(void) {
            column++;
        }

        void step(int length) {
            column += length;
        }
};
