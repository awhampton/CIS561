%{
#include <cstdio>
#include <iostream>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	int   ival;
	char *sval;
	char  cval;
}

// define the constant-string tokens:
%token CLASS
%token DEF
%token EXTENDS
%token IF
%token ELIF
%token ELSE
%token WHILE
%token RETURN

%token LESS
%token MORE
%token ATLEAST
%token ATMOST
%token EQUALS

%token AND
%token OR
%token NOT

%token LPAREN
%token RPAREN
%token LBRACE
%token RBRACE
%token COLON
%token SEMICOLON
%token GETS
%token COMMA
%token PERIOD

%token PLUS
%token MINUS
%token TIMES
%token DIVIDE

%token <sval> IDENT
%token <ival> INT_LIT
%token <sval> STRING_LIT

// precedence rules
%left AND OR
%precedence NOT
%left LESS MORE EQUALS ATMOST ATLEAST
%left PLUS MINUS
%left TIMES DIVIDE
%left PERIOD


%%

program:
	classes statements { cout << "done with a quack file!" << endl; }
	;

classes:
	classes class { cout << "got classes" << endl; }
	| /* empty */
	;

class:
    class_signature class_body { cout << "got class" << endl; }
	;

class_signature:
    class_sig_extends {cout << "got class signature extends" << endl; }
	| class_sig_no_extends {cout << "got class signature no extends" << endl; }
	;

class_sig_extends:
    CLASS IDENT LPAREN formal_args RPAREN EXTENDS IDENT { cout << "got class sig with extends:: " << $2 << endl; }
	;

class_sig_no_extends:
    CLASS IDENT LPAREN formal_args RPAREN { cout << "got class sig without extends:: " << $2 << endl; }
	;

formal_args:
    formal_arg { cout << "got formal args" << endl; }
	| /* empty */
	;

formal_arg:
	IDENT COLON IDENT formal_arg_repetitions { cout << "got formal arg:: " << $1 << " : " << $3 << endl; }
	;

formal_arg_repetitions:
	formal_arg_repetitions formal_arg_repetition { cout << "got formal arg repetitions" << endl; }
	| /* empty */
	;

formal_arg_repetition:
	COMMA IDENT COLON IDENT { cout << "got formal arg repetition:: " << $2 << " : " << $4 << endl; }
	;

class_body:
	LBRACE statements methods RBRACE { cout << "got class body" << endl; }
	;

statements:
	statements statement { cout << "got statement" << endl; }
	| /* empty */
	;

statement:
	IF r_expr statement_block elifs opt_else { cout << "statement if" << endl; }
	;

statement:
	WHILE r_expr statement_block { cout << "statement while" << endl; }
	;

statement:
	l_expr opt_ident GETS r_expr SEMICOLON { cout << "statement assignment" << endl; }
	;

statement:
	r_expr SEMICOLON { cout << "statement r_expr" << endl; }
	;

statement:
	RETURN r_expr SEMICOLON { cout << "statement return r_expr" << endl; }
	;

statement:
	RETURN SEMICOLON { cout << "statement return empty" << endl; }
	;

methods:
	methods method { cout << "got methods" << endl; }
	| /* empty */
	;

method:
	DEF IDENT LPAREN formal_args RPAREN opt_ident statement_block {cout << "got method:: " << $2 << endl;}
	;

opt_ident:
	COLON IDENT {cout << "got optional identifier:: " << $2 << endl;}
	| /* empty */
	;

statement_block:
	LBRACE statements RBRACE {cout << "got statement block" << endl;}
	;

elifs:
	elifs elif_rule { cout << "got an elif rule" << endl; }
	| /* empty */
	;

elif_rule:
	ELIF r_expr statement_block { cout << "got an elif" << endl; }
	;

opt_else:
	else_rule { cout << "got an else rule" << endl; }
	| /* empty */
	;

else_rule:
	ELSE statement_block { cout << "got an else" << endl; }
	;

l_expr:
	IDENT { cout << "got left expression ident:: " << $1 << endl; }
	;

l_expr:
	r_expr PERIOD IDENT { cout << "got left expression r_expr.ident:: " << $3 << endl; }
	;

r_expr:
	STRING_LIT { cout << "right expression string lit:: " << $1 << endl; }
	;

r_expr:
	INT_LIT { cout << "right expression int lit:: " << $1 << endl; }
	;

r_expr:
	l_expr { cout << "right expression l_expr" << endl; }
	;

r_expr:
	r_expr PLUS r_expr { cout << "right expression r_expr + r_expr" << endl; }
	;

r_expr:
	r_expr MINUS r_expr { cout << "right expression r_expr - r_expr" << endl; }
	;

r_expr:
	r_expr TIMES r_expr { cout << "right expression r_expr * r_expr" << endl; }
	;

r_expr:
	r_expr DIVIDE r_expr { cout << "right expression r_expr / r_expr" << endl; }
	;

r_expr:
	LPAREN r_expr RPAREN { cout << "right expression (r_expr)" << endl; }
	;

r_expr:
	r_expr EQUALS r_expr { cout << "right expression r_expr == r_expr" << endl; }
	;

r_expr:
	r_expr ATMOST r_expr { cout << "right expression r_expr <= r_expr" << endl; }
	;

r_expr:
	r_expr LESS r_expr { cout << "right expression r_expr < r_expr" << endl; }
	;

r_expr:
	r_expr ATLEAST r_expr { cout << "right expression r_expr >= r_expr" << endl; }
	;

r_expr:
	r_expr MORE r_expr { cout << "right expression r_expr > r_expr" << endl; }
	;

r_expr:
	r_expr AND r_expr { cout << "right expression r_expr and r_expr" << endl; }
	;

r_expr:
	r_expr OR r_expr { cout << "right expression r_expr or r_expr" << endl; }
	;

r_expr:
	NOT r_expr { cout << "right expression not r_expr" << endl; }
	;

r_expr:
	r_expr PERIOD IDENT LPAREN actual_args RPAREN { cout << "right expression method call" << endl; }
	;

r_expr:
	IDENT LPAREN actual_args RPAREN { cout << "right expression class instance" << endl; }
	;

actual_args:
    actual_arg { cout << "got actual args" << endl; }
	| /* empty */
	;

actual_arg:
	r_expr actual_arg_repetitions { cout << "got actual arg" << endl; }
	;

actual_arg_repetitions:
	actual_arg_repetitions actual_arg_repetition { cout << "got actual arg repetitions" << endl; }
	| /* empty */
	;

actual_arg_repetition:
	COMMA r_expr { cout << "got actual arg repetition" << endl; }
	;

%%

int main(int, char**) {
	// open a file handle to a particular file:
	FILE *myfile = fopen("sample.qk", "r");
	// make sure it's valid:
	if (!myfile) {
		cout << "I can't open file!" << endl;
		return -1;
	}
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));

}

void yyerror(const char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}
