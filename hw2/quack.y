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
extern int num_errors;

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
	condition_node           *conditional_type;
	list<condition_node *>   *conditionals_type;
	list<statement_node *>   *statements_type;
	list<class_node *>       *classes_type;
	pgm_node                 *prog_type;
}


// declare types
%type <conditionals_type>     elifs
%type <conditional_type>      elif_rule
%type <expr_type>             l_expr r_expr
%type <opt_ident_type>        opt_ident
%type <method_type>           method
%type <methods_type>          methods
%type <actual_arg_type>       actual_arg_repetition
%type <actual_args_type>      actual_arg_repetitions actual_arg actual_args
%type <formal_arg_type>       formal_arg_repetition
%type <formal_args_type>      formal_arg_repetitions formal_arg formal_args
%type <class_body_type>       class_body
%type <class_signature_type>  class_signature class_sig_extends class_sig_no_extends
%type <statement_type>        statement
%type <class_type>            class
%type <statements_type>       statements statement_block opt_else else_rule
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
%precedence NEG
%left PERIOD


%%

program:
	classes statements { $$ = new pgm_node($1, $2); root = $$; }
	;

classes:
	classes class { $$ = $1; $1->push_back($2); }
	| /* empty */ { $$ = new list<class_node *>(); }
	;

class:
    class_signature class_body { $$ = new class_node($1, $2); }
	;

class_signature:
    class_sig_extends { $$ = $1; }
	| class_sig_no_extends { $$ = $1; }
	;

class_sig_extends:
    CLASS IDENT LPAREN formal_args RPAREN EXTENDS IDENT { $$ = new class_signature_node($2, $7, $4); }
	;

class_sig_no_extends:
    CLASS IDENT LPAREN formal_args RPAREN { $$ = new class_signature_node($2, $4); }
	;

formal_args:
    formal_arg    { $$ = $1; }
	| /* empty */ { $$ = new list<formal_arg_node *>(); }
	;

formal_arg:
	IDENT COLON IDENT formal_arg_repetitions { $4->push_front( new formal_arg_node($1, $3) ); $$ = $4; }
	;

formal_arg_repetitions:
	formal_arg_repetitions formal_arg_repetition { $$ = $1; $1->push_back($2); }
	| formal_arg_repetitions error COMMA { } /* skip until next comma */
	| /* empty */ { $$ = new list<formal_arg_node *>(); }
	;

formal_arg_repetition:
	COMMA IDENT COLON IDENT { $$ = new formal_arg_node($2, $4); }
	;

class_body:
	LBRACE statements methods RBRACE { $$ = new class_body_node($2, $3); }
	;

statements:
	statements statement { $$ = $1; $1->push_back($2); }
	| statements error '\n' { }
	| /* empty */        { $$ = new list<statement_node *>(); }
	;

statement:
	IF r_expr statement_block elifs opt_else { $$ = new if_elifs_else_node(new condition_node($2,$3), $4, $5); }
	;

statement:
	WHILE r_expr statement_block { $$ = new while_node(new while_condition_node($2, $3)); }
	;

statement:
	l_expr opt_ident GETS r_expr SEMICOLON { $$ = new assignment_node($1, $2, $4); }
	;

statement:
	r_expr SEMICOLON { $$ = new bare_expr_node($1); }
	;

statement:
	RETURN r_expr SEMICOLON { $$ = new return_node($2); }
	;

statement:
	RETURN SEMICOLON { $$ = new return_node(); }
	;

methods:
	methods method { $$ = $1; $1->push_back($2); }
	| /* empty */  { $$ = new list<method_node *>(); }
	;

method:
	DEF IDENT LPAREN formal_args RPAREN opt_ident statement_block { $$ = new method_node($2, $6, $4, $7); }
	;

opt_ident:
	COLON IDENT { $$ = $2; }
	| /* empty */ { $$ = (char *) "Obj"; }
	;

statement_block:
	LBRACE statements RBRACE { $$ = $2; }
	;

elifs:
	elifs elif_rule { $$ = $1; $1->push_back($2); }
	| /* empty */   { $$ = new list<condition_node *>(); }
	;

elif_rule:
	ELIF r_expr statement_block { $$ = new condition_node($2, $3); }
	;

opt_else:
	else_rule { $$ = $1; }
	| /* empty */ { $$ = $$ = new list<statement_node *>(); }
	;

else_rule:
	ELSE statement_block { $$ = $2; }
	;

l_expr:
	IDENT { $$ = new ident_node($1); }
	;

l_expr:
	r_expr PERIOD IDENT { $$ = new access_node($1, $3); }
	;

r_expr:
	STRING_LIT { $$ = new strlit_node($1); }
	;

r_expr:
	INT_LIT { $$ = new intlit_node($1); }
	;

r_expr:
	l_expr { $$ = $1; }
	;

r_expr:
	r_expr PLUS r_expr { $$ = new method_call_node($1, "PLUS", $3); }
	;

r_expr:
	r_expr MINUS r_expr { $$ = new method_call_node($1, "MINUS", $3); }
	;

r_expr:
	MINUS r_expr %prec NEG { $$ = new method_call_node(new intlit_node(0), "MINUS", $2); }
	;

r_expr:
	r_expr TIMES r_expr { $$ = new method_call_node($1, "TIMES", $3); }
	;

r_expr:
	r_expr DIVIDE r_expr { $$ = new method_call_node($1, "DIVIDE", $3); }
	;

r_expr:
	LPAREN r_expr RPAREN { $$ = $2; }
	;

r_expr:
	r_expr EQUALS r_expr { $$ = new method_call_node($1, "EQUALS", $3); }
	;

r_expr:
	r_expr ATMOST r_expr { $$ = new method_call_node($1, "ATMOST", $3); }
	;

r_expr:
	r_expr LESS r_expr { $$ = new method_call_node($1, "LESS", $3); }
	;

r_expr:
	r_expr ATLEAST r_expr { $$ = new method_call_node($1, "ATLEAST", $3); }
	;

r_expr:
	r_expr MORE r_expr { $$ = new method_call_node($1, "MORE", $3); }
	;

r_expr:
	r_expr AND r_expr { $$ = new and_node($1, $3); }
	;

r_expr:
	r_expr OR r_expr { $$ = new or_node($1, $3); }
	;

r_expr:
	NOT r_expr { $$ = new not_node($2); }
	;

r_expr:
	r_expr PERIOD IDENT LPAREN actual_args RPAREN { $$ = new method_call_node($1, $3, $5); }
	;

r_expr:
	IDENT LPAREN actual_args RPAREN { $$ = new class_instantiation_node($1, $3); }
	;

actual_args:
    actual_arg { $$ = $1; }
	| /* empty */ { $$ = new list<actual_arg_node *>(); }
	;

actual_arg:
	r_expr actual_arg_repetitions { $2->push_front( new actual_arg_node($1) ); $$ = $2; }
	;

actual_arg_repetitions:
	actual_arg_repetitions actual_arg_repetition { $$ = $1; $1->push_back($2); }
	| /* empty */ { $$ = new list<actual_arg_node *>(); }
	;

actual_arg_repetition:
	COMMA r_expr { $$ = new actual_arg_node($2); }
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

	// if everything is OK continue processing with AST
	if(num_errors == 0){
		cout << "Finished parse with no errors" << endl;

		// crawl the AST
		// cout << endl;
		// crawl_ast(root);
		// cout << endl;
	}
	// else print the number of errors on stdout
	else{
		cout << "Found " << num_errors << " errors!" << endl;
	}

}
