/*
*  CIS 561: HW 4
*  Garrett Morrison
*  Andrew Hampton
*
*  I used the following tutorial as a starting point: http://aquamentus.com/flex_bison.html
*/


%{
#include <cstdio>
#include <iostream>
#include <string>
#include "quack.h"
using namespace std;
#define YY_DECL extern "C" int yylex()
#include "quack.tab.h"
#include "log.h"

extern char *INFILE_NAME;
extern DEBUG_STREAM LOG;

int num_errors = 0;
void yyerror (const char *errmsg) {

    num_errors++;
    string msg = string(errmsg) + " ('" + string(yytext) + "')";
    LOG.insert("SyntaxError", yylineno, msg);
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
=                                          { yylval.ival = yylineno; return GETS; }
,                                          { return COMMA; }
\.                                         { return PERIOD; }
class                                      { return CLASS; }
def                                        { return DEF; }
extends                                    { return EXTENDS; }
if                                         { yylval.ival = yylineno; return IF; }
elif                                       { yylval.ival = yylineno; return ELIF; }
else                                       { yylval.ival = yylineno; return ELSE; }
while                                      { yylval.ival = yylineno; return WHILE; }
return                                     { yylval.ival = yylineno; return RETURN; }
and                                        { yylval.ival = yylineno; return AND; }
or                                         { yylval.ival = yylineno; return OR; }
not                                        { yylval.ival = yylineno; return NOT; }
\<=                                        { yylval.ival = yylineno; return ATMOST; }
==                                         { yylval.ival = yylineno; return EQUALS; }
\>=                                        { yylval.ival = yylineno; return ATLEAST; }
\<                                         { yylval.ival = yylineno; return LESS; }
\>                                         { yylval.ival = yylineno; return MORE; }
\+                                         { yylval.ival = yylineno; return PLUS; }
\-                                         { yylval.ival = yylineno; return MINUS; }
\*                                         { yylval.ival = yylineno; return TIMES; }
\/                                         { yylval.ival = yylineno; return DIVIDE; }

[a-zA-Z_][a-zA-Z0-9_]*                     { struct string_with_linenum t; t.s = strdup(yytext); t.ln = yylineno; yylval.swln = t; return IDENT; }
[0-9]+                                     { struct int_with_linenum t; t.n = atoi(yytext); t.ln = yylineno; yylval.iwln = t; return INT_LIT; }
\"(([\\][0btnrf\"\\])|[^\"\\\n])*\"        { struct string_with_linenum t; t.s = strdup(yytext); t.ln = yylineno; yylval.swln = t; return STRING_LIT; }
\"(([\\].)|[^\"\\\n])*\"                   { yyerror("invalid string literal"); struct string_with_linenum t; t.s = strdup(yytext); t.ln = yylineno; yylval.swln = t; return STRING_LIT; }
\"(([\\][.])|[^\"\\\n])*\n                 { yyerror("forgot to close string literal"); struct string_with_linenum t; t.s = strdup(yytext); t.ln = yylineno; yylval.swln = t; return STRING_LIT; }
\"\"\"(.?.?[^\"])*\"\"\"                   { struct string_with_linenum t; t.s = strdup(yytext); t.ln = yylineno; yylval.swln = t; return STRING_LIT; }

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
