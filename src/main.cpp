#include <cstdio>
#include <algorithm>
#include <cassert>
#include <vector>
#include <getopt.h>

#include "lexer.h"


namespace {
    constexpr auto stringify_token(Token const &t)
    {
        switch(t.type) {
            case TokenType::Identifier: return "id";
            case TokenType::Integer:    return "integer";
            case TokenType::Character:  return "character";
            case TokenType::String:     return "string";
            case TokenType::Error:      return "error";
            case TokenType::Symbol:     [[fallthrough]];
            case TokenType::Keyword:    [[fallthrough]];
            case TokenType::End:        [[fallthrough]];
            default:                    return "";
        }
    }
} //anonymous namespace


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
                    std::vector<Token> const tokens = l.get_tokens();
                    std::for_each(std::begin(tokens), std::end(tokens),
                            [] (const auto &t) {
                                printf("%d:%d %s %s\n", t.position.line, t.position.cols, stringify_token(t), t.value.c_str());
                            });
                }

                break;
            default:
                fprintf(stderr, "Unknown option\n");
        }
    }
}
