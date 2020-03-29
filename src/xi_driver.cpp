#include "xi_driver.h"

#include <cstdio>
#include <cassert>
#include <fstream>

void XIDriver::trace_scanning(const std::vector<std::string> &filenames)
{
    for (std::string filename : filenames) {
        std::ifstream in(filename, std::ifstream::in);

        assert(in.is_open() && in.good());

        lexer.switch_streams(&in, 0);

        for (TokenType type = lexer.yylex(ctx);
                type != TokenType::End;
                type = lexer.yylex(ctx)) {
            if (type == TokenType::Error) {
                puts("error");
                break;
            }

            std::cout << ctx.get_value() << std::endl;
        }
    }
}
