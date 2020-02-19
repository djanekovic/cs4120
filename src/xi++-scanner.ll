%{
#include "xi_lexer.h"
#define YY_NO_UNISTD_H
#define yyterminate() return TokenType::End;
#define YY_USER_ACTION ctx.step();
%}

%option debug noyywrap

ID      [a-z][a-zA-Z0-9]*
DIGIT   [0-9]
KEYWORD (use|if|while|else|return|length|int|bool|true|false)
STRING \".*\"

%%
" "             {
                    ctx.step();
                }
{STRING}        {   printf("Procitao sam string %s\n", YYText()); }
\n              {   ctx.new_line(); }
[-]?{DIGIT}     {
                    Token new_token(TokenType::Integer, std::string(YYText()));
                    ctx.set_token(new_token);
                    return TokenType::Integer;
                }
{KEYWORD}       {
                    Token new_token(TokenType::Keyword, std::string(YYText()));
                    ctx.set_token(new_token);
                    return TokenType::Keyword;
                }
"-"|"!"|"*"|">>"|"/"|"%"|"+"|"-"|"<"|"<="|">="|">"|"=="|"!="|"&"|"|"       {
                    Token new_token(TokenType::Symbol, std::string(YYText()));
                    ctx.set_token(new_token);
                    return TokenType::Symbol;
                }
%%

int yyFlexLexer::yylex() {
    std::cerr << "This should never be called..." << std::endl;
    exit(1);
}
