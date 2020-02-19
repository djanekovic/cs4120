#pragma once

#ifndef YY_DECL
#define YY_DECL \
    TokenType XILexer::yylex(ParserContext &ctx)
#endif

#undef yyFlexLexer
#include <FlexLexer.h>

#include "parser_context.h"
#include "token.h"

class XILexer: public yyFlexLexer {
    public:
        using yyFlexLexer::yylex;

        TokenType yylex(ParserContext &ctx);
};
