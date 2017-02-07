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
#include <map>
#include <set>
#include <iterator>
#include <algorithm>
#include "quack.h"
using namespace std;

// the root of the abstract syntax tree
pgm_node *root;

// helpful globals for class structure errors
string CLASS_CYCLE_SUPERCLASS;
string CLASS_CYCLE_SUBCLASS;
string MULTIPLE_SUBCLASS;
set<string> BUILTIN_CLASSES;
set<string> CLASSES_FOUND;
set<string> CONSTRUCTOR_CALLS;

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

// build the class hierarchy tree (represented as an adjacency list)
//   note: we can imagine the class hierarchy as a directed tree rooted at "Obj", with
//         edges pointing from the superclass to the sublcass
map<string, list<string> > build_class_graph(pgm_node *r){
	list<class_node *> classes = *(r->classes);
	map<string, list<string> > res;
	for(set<string>::iterator itr = BUILTIN_CLASSES.begin(); itr != BUILTIN_CLASSES.end(); ++itr){
		if(*itr != "Obj"){
			res["Obj"].push_back(*itr);
		}
	}
	for(list<class_node *>::iterator itr = classes.begin(); itr != classes.end(); ++itr){
		string class_name = (*itr)->signature->class_name;
		string class_extends = (*itr)->signature->class_extends;
		res[class_extends].push_back(class_name);
	}
	return res;
}

// get a set containing all the class names
set<string> get_class_names(pgm_node *r){
	list<class_node *> classes = *(r->classes);
	set<string> res;
	for(list<class_node *>::iterator itr = classes.begin(); itr != classes.end(); ++itr){
		string class_name = (*itr)->signature->class_name;
		res.insert(class_name);
	}
	return res;
}

// get a set containing all the class extends
set<string> get_class_extends(pgm_node *r){
	list<class_node *> classes = *(r->classes);
	set<string> res;
	for(list<class_node *>::iterator itr = classes.begin(); itr != classes.end(); ++itr){
		string class_extends = (*itr)->signature->class_extends;
		res.insert(class_extends);
	}
	return res;
}

// crawl the class graph
void crawl_class_graph(map<string, list<string> > cg, string r){
	cout << r << endl;
	for(list<string>::iterator itr = cg[r].begin(); itr != cg[r].end(); ++itr){
		crawl_class_graph(cg, *itr);
	}
	return;
}

// check that the class graph is a tree with one component
// return: 0 - good; 1 - has cycle; 2 - multiple components; 3 - multiple inheritance
int check_class_graph(map<string, list<string> > cg, string r){
	set<string> closed_set;
	set<string> seen_set;
	list<string> stack;
	stack.push_back(r);
	seen_set.insert(r);
	while(!stack.empty()){
		string current = stack.back();
		// cout << "current: " << current << endl;
		stack.pop_back();
		closed_set.insert(current);
		for(list<string>::iterator itr = cg[current].begin(); itr != cg[current].end(); ++itr){
			// cout << "  neighbor: " << *itr << endl;

			if(closed_set.find(*itr) == closed_set.end()){
				stack.push_back(*itr);
			}
			else{
				CLASS_CYCLE_SUPERCLASS = current;
				CLASS_CYCLE_SUBCLASS = *itr;
				return 1;  // we have found a cycle
			}

			if(seen_set.find(*itr) == seen_set.end()){
				seen_set.insert(*itr);
			}
			else{
				MULTIPLE_SUBCLASS = *itr;
				return 3;  // class has two superclasses
			}
		}
	}

	// set the global containing the classes we found in the search
	CLASSES_FOUND = closed_set;

	if(closed_set.size() < cg.size()){
		return 2;  // the search didn't find all the classes
	}

	// if we made it here, everything looks good!
	return 0;
}

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

// check for class constructor call
void recursive_crawl_constructors(node *n){
	if( n->type_of_node == "expr" && n->type_of_expression == "class_instantiation"){
		CONSTRUCTOR_CALLS.insert(n->class_name);
	}

	list<node *> children = n->get_children();
	for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
		recursive_crawl_constructors(*itr);
	}

	return;
}

// crawl the AST, looking for class instantiations
void get_constructor_names(pgm_node *r){
	recursive_crawl_constructors((node*) r);
}

// populate the builtin class set
void populate_builtin_classes(void){
	BUILTIN_CLASSES.insert("Obj");
	BUILTIN_CLASSES.insert("String");
	BUILTIN_CLASSES.insert("Integer");
	BUILTIN_CLASSES.insert("Boolean");
	BUILTIN_CLASSES.insert("Nothing");
}


int main(int argc, char **argv) {

	// populate the builtin class set
	populate_builtin_classes();

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

		// make the class hierarchy graph
		map<string, list<string> > class_graph = build_class_graph(root);

		// crawl the class graph
		// cout << endl;
		// crawl_class_graph(class_graph, "Obj");
		// cout << endl;

		// check that the class graph is a tree with one connected component
		int class_res = check_class_graph(class_graph, "Obj");
		if(class_res == 0){
			cerr << "class structure good!" << endl;
		}
		else if(class_res == 1){
			cerr << "cycle detected in class structure!" << endl;
			cerr << "  (" << CLASS_CYCLE_SUPERCLASS << " -> " << CLASS_CYCLE_SUBCLASS << " is on the cycle)" << endl;
		}
		else if(class_res == 2){
			set<string> class_extends = get_class_extends(root);
			set<string> missing;
			set_difference(class_extends.begin(), class_extends.end(), CLASSES_FOUND.begin(), CLASSES_FOUND.end(), inserter(missing, missing.end()));
			cerr << "class definition missing! tried to extend the following undefined classes: " << endl;
			for(set<string>::iterator itr = missing.begin(); itr != missing.end(); ++itr){
				cerr << "  " << *itr << endl;
			}
		}
		else if(class_res == 3){
			cerr << "multiple inheritance! class defined twice?" << endl;
			cerr << "  (" << MULTIPLE_SUBCLASS << " inherits from more than one class)" << endl;
		}

		// check that constructor calls are valid
		get_constructor_names(root);  // stored in global CONSTRUCTOR_CALLS

		// cout << "classes found:" << endl;
		// for(set<string>::iterator itr = CLASSES_FOUND.begin(); itr != CLASSES_FOUND.end(); ++itr){
		// 	cerr << "  " << *itr << endl;
		// }

		// cout << "constructor calls:" << endl;
		// for(set<string>::iterator itr = CONSTRUCTOR_CALLS.begin(); itr != CONSTRUCTOR_CALLS.end(); ++itr){
		// 	cerr << "  " << *itr << endl;
		// }

		set<string> missing;
		set_difference(CONSTRUCTOR_CALLS.begin(), CONSTRUCTOR_CALLS.end(), CLASSES_FOUND.begin(), CLASSES_FOUND.end(), inserter(missing, missing.end()));
		if(!missing.empty()){
			cerr << "class definition missing! tried to construct the following undefined classes: " << endl;
			for(set<string>::iterator itr = missing.begin(); itr != missing.end(); ++itr){
				cerr << "  " << *itr << endl;
			}
		}

	}
	// else print the number of errors on stdout
	else{
		cout << "Found " << num_errors << " errors!" << endl;
	}

}
