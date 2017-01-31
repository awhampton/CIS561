


%{
#include <cstdio>
#include <iostream>
#include "tt.h"
using namespace std;
#define YY_DECL extern "C" int yylex()
#include "tt.tab.h"
%}
%option yylineno
%option warn nodefault
%option noyywrap
%x COMMENTS_C
%x COMMENTS_LINE
%%
[ \t\r\v\f]                                ; // whitespace
[0-9]+                                     { yylval.ival = atoi(yytext);  return INT_LIT; }
[+]                                        { return yytext[0]; }
\n                                         { }

<<EOF>>                                    { return EOF; }
.                                          { fprintf(stderr, "something bad on line %d: %s\n", yylineno, yytext); }
%%
