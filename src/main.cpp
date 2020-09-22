#include <cstdio>
#include <algorithm>
#include <cassert>
#include <vector>
#include <getopt.h>

#include "lexer.h"

struct token_formater
{
    void operator()(const Token &t) {
        switch(t.type) {
            case TokenType::Identifier:
                printf("%d:%d id %s\n", t.position.line, t.position.cols, t.value.c_str());
                break;
            case TokenType::Integer:
                printf("%d:%d integer %s\n", t.position.line, t.position.cols, t.value.c_str());
                break;
            case TokenType::Character:
                printf("%d:%d character %s\n", t.position.line, t.position.cols, t.value.c_str());
                break;
            case TokenType::String:
                printf("%d:%d string %s\n", t.position.line, t.position.cols, t.value.c_str());
                break;
            case TokenType::Symbol:
                printf("%d:%d %s\n", t.position.line, t.position.cols, t.value.c_str());
                break;
            case TokenType::Keyword:
                printf("%d:%d %s\n", t.position.line, t.position.cols, t.value.c_str());
                break;
            case TokenType::Error:
                printf("%d:%d error:%s\n", t.position.line, t.position.cols, t.value.c_str());
                break;
            default:
                break;
        }
    }
};

int main(int argc, char **argv)
{
    struct option long_options[] = {
        { "help", no_argument, 0, 'h' },
        { "lex", no_argument, 0, 'l'},
        { 0, 0, 0, 0}
    };

    while (1) {
        int option_index = 0, c = 0;
        c = getopt_long(argc, argv, "", long_options, &option_index);

        if (c == -1) {
            break;
        }

        switch(c) {
            case 'h':
                return 0;
                break;
            case 'l':
                assert(optind < argc);

                for (int i = optind; i < argc; i++) {
                    Lexer l (argv[i]);
                    std::vector<Token> tokens = l.get_tokens();
                    std::for_each(std::begin(tokens), std::end(tokens), token_formater());
                }

                break;
            default:
                fprintf(stderr, "Unknown option\n");
        }

    }
}
