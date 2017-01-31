/*
*  CIS 561: HW 1
*  Andrew Hampton
*
*  I used the following tutorial as a starting point: http://aquamentus.com/flex_bison.html
*/


%{
#include <cstdio>
#include <iostream>
using namespace std;
#define YY_DECL extern "C" int yylex()
#include "quack.tab.h"
%}
%option yylineno
%option warn nodefault
%option noyywrap
%x COMMENTS_C
%x COMMENTS_LINE
%%
[ \t\r\v\f]                                ; // whitespace
\(                                         { return LPAREN; }
\)                                         { return RPAREN; }
\{                                         { return LBRACE; }
\}                                         { return RBRACE; }
:                                          { return COLON; }
;                                          { return SEMICOLON; }
=                                          { return GETS; }
,                                          { return COMMA; }
\.                                         { return PERIOD; }
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

[a-zA-Z_][a-zA-Z0-9_]*                     { yylval.sval = strdup(yytext); return IDENT; }
[0-9]+                                     { yylval.ival = atoi(yytext);   return INT_LIT; }
\"(([\\][0btnrf\"\\])|[^\"\\\n])*\"        { yylval.sval = strdup(yytext); return STRING_LIT; }
\"(([\\].)|[^\"\\\n])*\"                   { fprintf(stderr, "invalid string literal on line %d: %s\n", yylineno, yytext); return STRING_LIT; }
\"(([\\][.])|[^\"\\\n])*\n                 { fprintf(stderr, "forgot to close string literal on line %d: %s\n", yylineno, yytext); return STRING_LIT; }
\"\"\"(.?.?[^\"])*\"\"\"                   { yylval.sval = strdup(yytext); return STRING_LIT; }

\n                                         { }

\/\*                                       { BEGIN(COMMENTS_C); }
<COMMENTS_C>\*\/                           { BEGIN(INITIAL); }
<COMMENTS_C>\n                             { }
<COMMENTS_C>.                              ;

\/\/                                       { BEGIN(COMMENTS_LINE); }
<COMMENTS_LINE>\n                          { BEGIN(INITIAL); }
<COMMENTS_LINE>.                           ;

<<EOF>>                                    { return EOF; }
.                                          { fprintf(stderr, "something bad on line %d: %s\n", yylineno, yytext); }
%%
