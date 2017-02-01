/*
*  CIS 561: HW 2
*  Andrew Hampton
*
*  I used the following tutorial as a starting point: http://aquamentus.com/flex_bison.html
*
*  For building the AST in bison, I referenced the following:
*  [1] http://www.progtools.org/compilers/tutorials/cxx_and_bison/cxx_and_bison.html
*  [2] http://web.eecs.utk.edu/~bvz/teaching/cs461Sp11/notes/parse_tree/
*/


%{
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "quack.h"
using namespace std;

// the root of the abstract syntax tree
pgm_node *root;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int yylineno;

extern void yyerror(const char *s);
char* INFILE_NAME;
%}


// the union
%union {
	int   ival;
	char *sval;
	char  cval;
	char                     *opt_ident_type;
	method_node              *method_type;
	list<method_node *>      *methods_type;
	actual_arg_node          *actual_arg_type;
	list<actual_arg_node *>  *actual_args_type;
	formal_arg_node          *formal_arg_type;
	list<formal_arg_node *>  *formal_args_type;
	class_body_node          *class_body_type;
	class_signature_node     *class_signature_type;
	class_node               *class_type;
	expr_node                *expr_type;
	statement_node           *statement_type;
	list<statement_node *>   *statements_type;
	list<class_node *>       *classes_type;
	pgm_node                 *prog_type;
}


// declare types
%type <expr_type>             l_expr r_expr
%type <opt_ident_type>        opt_ident
%type <method_type>           method
%type <methods_type>          methods
%type <actual_arg_type>       actual_arg_repetition
%type <actual_args_type>      actual_arg_repetitions
%type <actual_args_type>      actual_arg
%type <actual_args_type>      actual_args
%type <formal_arg_type>       formal_arg_repetition
%type <formal_args_type>      formal_arg_repetitions
%type <formal_args_type>      formal_arg
%type <formal_args_type>      formal_args
%type <class_body_type>       class_body
%type <class_signature_type>  class_signature
%type <class_signature_type>  class_sig_extends
%type <class_signature_type>  class_sig_no_extends
%type <statement_type>        statement
%type <class_type>            class
%type <statements_type>       statements
%type <statements_type>       statement_block
%type <classes_type>          classes
%type <prog_type>             program


// define the constant-string tokens
//  note: I was making too many typos so I gave these all names ...
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
	classes statements { cout << "done with a quack file!" << endl; $$ = new pgm_node($1, $2); root = $$; }
	;

classes:
	classes class { cout << "got more classes" << endl; $$ = $1; $1->push_back($2); }
	| /* empty */ { cout << "done with classes" << endl; $$ = new list<class_node *>(); }
	;

class:
    class_signature class_body { cout << "got class" << endl; $$ = new class_node($1, $2); }
	;

class_signature:
    class_sig_extends {cout << "got class signature extends" << endl; $$ = $1; }
	| class_sig_no_extends {cout << "got class signature no extends" << endl; $$ = $1; }
	;

class_sig_extends:
    CLASS IDENT LPAREN formal_args RPAREN EXTENDS IDENT { cout << "got class sig with extends:: " << $2 << endl; $$ = new class_signature_node($2, $7, $4); }
	;

class_sig_no_extends:
    CLASS IDENT LPAREN formal_args RPAREN { cout << "got class sig without extends:: " << $2 << endl; $$ = new class_signature_node($2, $4); }
	;

formal_args:
    formal_arg    { cout << "got formal args" << endl; $$ = $1; }
	| /* empty */ { $$ = new list<formal_arg_node *>(); }
	;

formal_arg:
	IDENT COLON IDENT formal_arg_repetitions { cout << "got formal arg:: " << $1 << " : " << $3 << endl; $4->push_front( new formal_arg_node($1, $3) ); $$ = $4; }
	;

formal_arg_repetitions:
	formal_arg_repetitions formal_arg_repetition { cout << "got formal arg repetitions" << endl; $$ = $1; $1->push_back($2); }
	| /* empty */ { cout << "done with formal arg repetitions" << endl; $$ = new list<formal_arg_node *>(); }
	;

formal_arg_repetition:
	COMMA IDENT COLON IDENT { cout << "got formal arg repetition:: " << $2 << " : " << $4 << endl; $$ = new formal_arg_node($2, $4); }
	;

class_body:
	LBRACE statements methods RBRACE { cout << "got class body" << endl; $$ = new class_body_node($2, $3); }
	;

statements:
	statements statement { cout << "got more statements" << endl; $$ = $1; $1->push_back($2); }
	| /* empty */        { cout << "done with statements" << endl; $$ = new list<statement_node *>(); }
	;

statement:
	IF r_expr statement_block elifs opt_else { cout << "statement if" << endl; $$ = new statement_node(); }
	;

statement:
	WHILE r_expr statement_block { cout << "statement while" << endl; $$ = new statement_node(); }
	;

statement:
	l_expr opt_ident GETS r_expr SEMICOLON { cout << "statement assignment" << endl; $$ = new statement_node(); }
	;

statement:
	r_expr SEMICOLON { cout << "statement r_expr" << endl; $$ = new statement_node(); }
	;

statement:
	RETURN r_expr SEMICOLON { cout << "statement return r_expr" << endl; $$ = new statement_node(); }
	;

statement:
	RETURN SEMICOLON { cout << "statement return empty" << endl; $$ = new statement_node(); }
	;

methods:
	methods method { cout << "got methods" << endl; $$ = $1; $1->push_back($2); }
	| /* empty */  { cout << "done with methods" << endl; $$ = new list<method_node *>(); }
	;

method:
	DEF IDENT LPAREN formal_args RPAREN opt_ident statement_block {cout << "got method:: " << $2 << endl; $$ = new method_node($2, $6, $4, $7); }
	;

opt_ident:
	COLON IDENT {cout << "got optional identifier:: " << $2 << endl; $$ = $2; }
	| /* empty */ { $$ = (char *) "Obj"; }
	;

statement_block:
	LBRACE statements RBRACE {cout << "got statement block" << endl; $$ = $2; }
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
	IDENT { cout << "got left expression ident:: " << $1 << endl; $$ = new expr_node(); }
	;

l_expr:
	r_expr PERIOD IDENT { cout << "got left expression r_expr.ident:: " << $3 << endl; $$ = new expr_node(); }
	;

r_expr:
	STRING_LIT { cout << "right expression string lit:: " << $1 << endl; $$ = new expr_node(); }
	;

r_expr:
	INT_LIT { cout << "right expression int lit:: " << $1 << endl; $$ = new expr_node(); }
	;

r_expr:
	l_expr { cout << "right expression l_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr PLUS r_expr { cout << "right expression r_expr + r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr MINUS r_expr { cout << "right expression r_expr - r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr TIMES r_expr { cout << "right expression r_expr * r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr DIVIDE r_expr { cout << "right expression r_expr / r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	LPAREN r_expr RPAREN { cout << "right expression (r_expr)" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr EQUALS r_expr { cout << "right expression r_expr == r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr ATMOST r_expr { cout << "right expression r_expr <= r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr LESS r_expr { cout << "right expression r_expr < r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr ATLEAST r_expr { cout << "right expression r_expr >= r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr MORE r_expr { cout << "right expression r_expr > r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr AND r_expr { cout << "right expression r_expr and r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr OR r_expr { cout << "right expression r_expr or r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	NOT r_expr { cout << "right expression not r_expr" << endl; $$ = new expr_node(); }
	;

r_expr:
	r_expr PERIOD IDENT LPAREN actual_args RPAREN { cout << "right expression method call" << endl; $$ = new expr_node(); }
	;

r_expr:
	IDENT LPAREN actual_args RPAREN { cout << "right expression class instance" << endl; $$ = new expr_node(); }
	;

actual_args:
    actual_arg { cout << "got actual args" << endl; $$ = $1; }
	| /* empty */ { $$ = new list<actual_arg_node *>(); }
	;

actual_arg:
	r_expr actual_arg_repetitions { cout << "got actual arg" << endl; $2->push_front( new actual_arg_node($1) ); $$ = $2; }
	;

actual_arg_repetitions:
	actual_arg_repetitions actual_arg_repetition { cout << "got actual arg repetitions" << endl; $$ = $1; $1->push_back($2); }
	| /* empty */ { cout << "done with actual arg repetitions" << endl; $$ = new list<actual_arg_node *>(); }
	;

actual_arg_repetition:
	COMMA r_expr { cout << "got actual arg repetition" << endl; $$ = new actual_arg_node($2); }
	;


%%


// pre-order traversal calling generic node methods
void recursive_crawl(node *n){
	n->speak();
	list<node *> children = n->get_children();

	for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
		recursive_crawl(*itr);
	}

	return;
}

// crawl the AST
void crawl_ast(pgm_node *r){
	recursive_crawl((node*) r);
}


int main(int argc, char **argv) {

	// see if there is a file, otherwise take input from stdin
	FILE *infile;
	INFILE_NAME = (char *) "stdin";
    if (argc > 1) {
    	if( !(infile = fopen(argv[1], "r"))){
  			perror(argv[1]);
  			exit(1);
        }
		INFILE_NAME = argv[1];
        yyin = infile;
    }

	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));

	// if we made it here, everything is OK
	cout << "Finished parse with no errors" << endl;

	// crawl the AST
	cout << endl;
	crawl_ast(root);
	cout << endl;

}

/*
void yyerror(const char *s) {
	cout << "parse error on line " << yylineno << endl;
	cout << "message: " <<  s << endl;
	cout << "stopping!" << endl;
	exit(1);
}
*/
