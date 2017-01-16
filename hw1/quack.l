%{
#include "quack.tab.h"
%}
%option yylineno
%option warn nodefault
%option header-file="lex.yy.h"
%option noyywrap
%x COMMENTS_C
%x COMMENTS_LINE
%%
[ \t\r\v\f]                                    ; // whitespace
[\(\)\{\}:;=,\.]                           { return yytext[0]; }  // terminal characters
class                                      { return CLASS; }
def                                        { return DEF; }
extends                                    { return EXTENDS; }
if                                         { return IF; }
elif                                       { return ELIF; }
else                                       { return ELSE; }
while                                      { return WHILE; }
return                                     { return RETURN; }
and                                        { return AND; }
or                                         { return OR; }
not                                        { return NOT; }
\<=                                        { return ATMOST; }
==                                         { return EQUALS; }
\>=                                        { return ATLEAST; }
\<                                         { return LESS; }
\>                                         { return MORE; }
\+                                         { return PLUS; }
\-                                         { return MINUS; }
\*                                         { return TIMES; }
\/                                         { return DIVIDE; }

[a-zA-Z_][a-zA-Z0-9_]*                     { return IDENT; }
[0-9]+                                     { return INT_LIT; }
\"(([\\][0btnrf\"\\])|[^\"\\\n])*\"        { return STRING_LIT; }
\"\"\"(.?.?[^\"])*\"\"\"                   { return STRING_LIT; }
\n                                         { }

\/\*                                       { BEGIN(COMMENTS_C); }
<COMMENTS_C>\*\/                           { BEGIN(INITIAL); }
<COMMENTS_C>\n                             { }   // increment line count in comments
<COMMENTS_C>.                              ;     // ignore everything

\/\/                                       { BEGIN(COMMENTS_LINE); }
<COMMENTS_LINE>\n                          { BEGIN(INITIAL); }
<COMMENTS_LINE>.                           ;

<<EOF>>                                    { return EOF; }
%%

//.                { printf("something bad\n"); }