%{
#include <cstdio>
#include <iostream>
#include "tt.h"
using namespace std;

// the root of the abstract syntax tree
pgm *root;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(const char *s);

%}


%union {
	int      ival;
	E_node  *e_node;
	pgm     *prog;
}

// declare types
%type <e_node> E
%type <prog> program

// define the constant-string tokens
%token '+'
%token <ival> INT_LIT

// precedence rules
%left '+'


%%

program : E { $$ = new pgm($1); root = $$; }
;

E: E '+' E  { cout << "got E + E rule" << endl;  $$ = new E_node($1, $3); }
   | INT_LIT { cout << "got int literal: " << $1 << endl;  $$ = new E_node($1); }

%%

void recursive_crawl(E_node *e){
	if(e->left != NULL){
		cout << '(';
		recursive_crawl(e->left);
	}
	if(e->got_int){
	cout << e->my_int;
	}
	else{
		cout << '+';
	}
	if(e->right != NULL){
		recursive_crawl(e->right);
		cout << ')';
	}
}

void crawl_sum(pgm *r){
	recursive_crawl(r->big_sum);
}

int main(int, char**) {
	// open a file handle to a particular file:
	FILE *myfile = fopen("tt.sample", "r");
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

	// crawl the tree
	crawl_sum(root);
	cout << endl;

}

void yyerror(const char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}
