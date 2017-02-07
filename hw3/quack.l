/*
*  CIS 561: HW 2
*  Andrew Hampton
*
*  I used the following tutorial as a starting point: http://aquamentus.com/flex_bison.html
*/


%{
#include <cstdio>
#include <iostream>
#include "quack.h"
using namespace std;
#define YY_DECL extern "C" int yylex()
#include "quack.tab.h"

extern char *INFILE_NAME;

int num_errors = 0;
int ERROR_LIMIT = 10;
void yyerror (const char *msg) {
    num_errors++;
    if(num_errors > ERROR_LIMIT){
        /* do nothing */
    }
    else if(num_errors == ERROR_LIMIT){
        fprintf(stderr, "\n");
        fprintf(stderr, "PARSE ERROR %d\n", num_errors);
        fprintf(stderr, "File: %s\n", INFILE_NAME);
        fprintf(stderr, "Near line %d: %s ('%s')\n", yylineno, msg, yytext);
        fprintf(stderr, "Too many errors! Suppressing message ...\n");
    }
    else{
        fprintf(stderr, "\n");
        fprintf(stderr, "PARSE ERROR %d\n", num_errors);
        fprintf(stderr, "File: %s\n", INFILE_NAME);
        fprintf(stderr, "Near line %d: %s ('%s')\n", yylineno, msg, yytext);
    }
}
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
\"(([\\].)|[^\"\\\n])*\"                   { yyerror("invalid string literal"); yylval.sval = strdup(yytext); return STRING_LIT; }
\"(([\\][.])|[^\"\\\n])*\n                 { yyerror("forgot to close string literal?"); yylval.sval = strdup(yytext); return STRING_LIT; }
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
.                                          { yyerror("lexical error"); }
%%
