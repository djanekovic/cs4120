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
            /*
            switch(type) {
                case TokenType::Character:
                    puts("Našao sam char");
                    break;
                case TokenType::End:
                    puts("Došao do kraja");
                    break;
                case TokenType::Id:
                    puts("Pročitao id");
                    break;
                case TokenType::Integer:
                    puts("Pročitao integer");
                    break;
                case TokenType::Keyword:
                    puts("Pročitao sam keyword");
                    break;
                case TokenType::String:
                    puts("Pročitao sam string");
                    break;
                case TokenType::Symbol:
                    puts("Pročitan simbol");
                    break;
            }
            */

            std::cout << ctx.get_value() << std::endl;
        }
    }
}
