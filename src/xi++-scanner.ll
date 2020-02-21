%{
#include "xi_lexer.h"
#define YY_NO_UNISTD_H
#define yyterminate() return TokenType::End;
#define HANDLE_TOKEN \
    Token new_token(type, std::string(YYText()), lineno(), column + 1); \
    ctx.set_token(new_token);                                           \
    column += YYLeng();                                                 \
    return type

int column = 0;
%}

%option debug noyywrap yylineno

ID      [a-z][a-zA-Z0-9'_]*
DIGIT   [0-9]
STRING  \".*\"
CHAR    \'[a-zA-Z]\'

%%
use       |
if        |
while     |
else      |
return    |
length    |
bool      |
int       |
true      |
false           {
                    TokenType type = TokenType::Keyword;
                    HANDLE_TOKEN;
                }
{ID}            {
                    TokenType type = TokenType::Id;
                    HANDLE_TOKEN;
                }
{CHAR}          {
                    TokenType type = TokenType::Character;
                    HANDLE_TOKEN;
                }
" "             {   column += 1;    }
{STRING}        {

                    TokenType type = TokenType::String;
                    HANDLE_TOKEN;
                }
[-]?[0-9]+      {
                    TokenType type = TokenType::Integer;
                    HANDLE_TOKEN;
                }
"-"         |
"!"         |
"*"         |
">>"        |
"/"         |
"%"         |
"+"         |
"<"         |
"<="        |
">="        |
">"         |
"=="        |
"!="        |
"&"         |
"["         |
"]"         |
":"         |
"("         |
")"         |
"{"         |
"}"         |
"="         |
";"         |
"_"             {
                    TokenType type = TokenType::Symbol;
                    HANDLE_TOKEN;
                }
"//".*$         {   /* eat one line comments */  }
\n              {   column = 0; }
.               {   return TokenType::Error;    }
%%

int yyFlexLexer::yylex() {
    std::cerr << "This should never be called..." << std::endl;
    exit(1);
}
