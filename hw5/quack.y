/*
*  CIS 561: HW 4
*  Garrett Morrison
*  Andrew Hampton
*
*  I used the following tutorial as a starting point: http://aquamentus.com/flex_bison.html
*
*  For building the AST in bison, I referenced the following:
*  [1] http://www.progtools.org/compilers/tutorials/cxx_and_bison/cxx_and_bison.html
*  [2] http://web.eecs.utk.edu/~bvz/teaching/cs461Sp11/notes/parse_tree/
*/


%{
#include <algorithm>
#include <array>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>
#include <vector>
#include "quack.h"
#include "log.h"

using namespace std;

// the root of the abstract syntax tree
pgm_node *root = NULL;

// helpful globals for class structure errors
string CLASS_CYCLE_SUPERCLASS;
string CLASS_CYCLE_SUBCLASS;
string MULTIPLE_SUBCLASS;
set<string> BUILTIN_CLASSES;
unordered_map< string, string > BUILTIN_VALUES;
set<string> CLASSES_FOUND;
set<string> CONSTRUCTOR_CALLS;

// globals for type checking
typedef vector< pair< string, list<string> > > VTable;
map<string, VTable> VTABLE_MAP;
map<string, map<string, string> > RT_MAP;
map<string, list<string> > CLASS_GRAPH;
typedef unordered_map< string, array< string, 2 > > SymTable;
unordered_map< string, SymTable > SymTables;
bool TYPE_CHECK_AGAIN;
bool BREAK_LOOP;

// globals for debugging
DEBUG_STREAM LOG(10);

// globals for code generation
vector<string> C;
map< string, map<string, SymTable> > LOCAL_SYMTABLES;
map<string, VTable> IMPLIED_ARGUMENT;
string OUTFILE_NAME = "generated.c";
string VAR_PREFIX = "ID_";

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
	int                     ival;
	char                    *sval;
	char                    cval;
    string_with_linenum     swln;
    int_with_linenum        iwln;
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
%type <opt_ident_type>        opt_ident_nothing opt_ident_obj
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
%token <ival> IF
%token <ival> ELIF
%token <ival> ELSE
%token <ival> WHILE
%token <ival> RETURN

%token <ival> LESS
%token <ival> MORE
%token <ival> ATLEAST
%token <ival> ATMOST
%token <ival> EQUALS

%token <ival> AND
%token <ival> OR
%token <ival> NOT

%token LPAREN
%token RPAREN
%token LBRACE
%token RBRACE
%token COLON
%token SEMICOLON
%token <ival> GETS
%token COMMA
%token PERIOD

%token <ival> PLUS
%token <ival> MINUS
%token <ival> TIMES
%token <ival> DIVIDE

%token <swln> IDENT
%token <iwln> INT_LIT
%token <swln> STRING_LIT

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
    CLASS IDENT LPAREN formal_args RPAREN EXTENDS IDENT { $$ = new class_signature_node($2.s, $7.s, $4, $2.ln); free($2.s); free($7.s); }
	;

class_sig_no_extends:
    CLASS IDENT LPAREN formal_args RPAREN { $$ = new class_signature_node($2.s, $4, $2.ln); free($2.s); }
	;

formal_args:
    formal_arg    { $$ = $1; }
	| /* empty */ { $$ = new list<formal_arg_node *>(); }
	;

formal_arg:
	IDENT COLON IDENT formal_arg_repetitions { $4->push_front( new formal_arg_node($1.s, $3.s, $1.ln) ); $$ = $4; free($1.s); free($3.s); }
	;

formal_arg_repetitions:
	formal_arg_repetitions formal_arg_repetition { $$ = $1; $1->push_back($2); }
	| formal_arg_repetitions error COMMA { } /* skip until next comma */
	| /* empty */ { $$ = new list<formal_arg_node *>(); }
	;

formal_arg_repetition:
	COMMA IDENT COLON IDENT { $$ = new formal_arg_node($2.s, $4.s, $2.ln); free($2.s); free($4.s); }
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
	IF r_expr statement_block elifs opt_else { $$ = new if_elifs_else_node(new condition_node($2, $3, $1), $4, $5); }
	;

statement:
	WHILE r_expr statement_block { $$ = new while_node(new while_condition_node($2, $3, $1)); }
	;

statement:
	l_expr opt_ident_obj GETS r_expr SEMICOLON { $$ = new assignment_node($1, $2, $4, $3); }
	;

statement:
	r_expr SEMICOLON { $$ = new bare_expr_node($1); }
	;

statement:
	RETURN r_expr SEMICOLON { $$ = new return_node($2, $1); }
	;

statement:
	RETURN SEMICOLON { $$ = new return_node($1); }
	;

methods:
	methods method { $$ = $1; $1->push_back($2); }
	| /* empty */  { $$ = new list<method_node *>(); }
	;

method:
	DEF IDENT LPAREN formal_args RPAREN opt_ident_nothing statement_block { $$ = new method_node($2.s, $6, $4, $7, $2.ln); free($2.s); }
	;

opt_ident_nothing:
	COLON IDENT { $$ = $2.s; }  /* note: small memory leak here that I'm struggling to fix! */
	| /* empty */ { char id[8] = "Nothing"; char* nothing = strdup(id); $$ = nothing; }  /* same as above */
	;

opt_ident_obj:
	COLON IDENT { $$ = $2.s; }  /* note: small memory leak here that I'm struggling to fix! */
	| /* empty */ { char id[4] = "Obj"; char* obj = strdup(id); $$ = obj; }  /* same as above */
	;

statement_block:
	LBRACE statements RBRACE { $$ = $2; }
	;

elifs:
	elifs elif_rule { $$ = $1; $1->push_back($2); }
	| /* empty */   { $$ = new list<condition_node *>(); }
	;

elif_rule:
	ELIF r_expr statement_block { $$ = new condition_node($2, $3, $1); }
	;

opt_else:
	else_rule { $$ = $1; }
	| /* empty */ { $$ = $$ = new list<statement_node *>(); }
	;

else_rule:
	ELSE statement_block { $$ = $2; }
	;

l_expr:
	IDENT { $$ = new ident_node($1.s, $1.ln); free($1.s); }
	;

l_expr:
	r_expr PERIOD IDENT { $$ = new access_node($1, $3.s, $3.ln); free($3.s); }
	;

r_expr:
	STRING_LIT { $$ = new strlit_node($1.s, $1.ln); free($1.s); }
	;

r_expr:
	INT_LIT { $$ = new intlit_node($1.n, $1.ln); }
	;

r_expr:
	l_expr { $$ = $1; }
	;

r_expr:
	r_expr PLUS r_expr { $$ = new method_call_node($1, "PLUS", $3, $2); }
	;

r_expr:
	r_expr MINUS r_expr { $$ = new method_call_node($1, "MINUS", $3, $2); }
	;

r_expr:
	MINUS r_expr %prec NEG { $$ = new method_call_node(new intlit_node(0, $1), "MINUS", $2, $1); }
	;

r_expr:
	r_expr TIMES r_expr { $$ = new method_call_node($1, "TIMES", $3, $2); }
	;

r_expr:
	r_expr DIVIDE r_expr { $$ = new method_call_node($1, "DIVIDE", $3, $2); }
	;

r_expr:
	LPAREN r_expr RPAREN { $$ = $2; }
	;

r_expr:
	r_expr EQUALS r_expr { $$ = new method_call_node($1, "EQUALS", $3, $2); }
	;

r_expr:
	r_expr ATMOST r_expr { $$ = new method_call_node($1, "ATMOST", $3, $2); }
	;

r_expr:
	r_expr LESS r_expr { $$ = new method_call_node($1, "LESS", $3, $2); }
	;

r_expr:
	r_expr ATLEAST r_expr { $$ = new method_call_node($1, "ATLEAST", $3, $2); }
	;

r_expr:
	r_expr MORE r_expr { $$ = new method_call_node($1, "MORE", $3, $2); }
	;

r_expr:
	r_expr AND r_expr { $$ = new and_node($1, $3, $2); }
	;

r_expr:
	r_expr OR r_expr { $$ = new or_node($1, $3, $2); }
	;

r_expr:
	NOT r_expr { $$ = new not_node($2, $1); }
	;

r_expr:
	r_expr PERIOD IDENT LPAREN actual_args RPAREN { $$ = new method_call_node($1, $3.s, $5, $3.ln); free($3.s); }
	;

r_expr:
	IDENT LPAREN actual_args RPAREN { $$ = new class_instantiation_node($1.s, $3, $1.ln); free($1.s); }
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

/////////////////////////////////
// helper functions
/////////////////////////////////

// code generation functions

// note: this one is only used for the main block
void local_variable_declarations(string class_name, string method_name){
    SymTable local_symtable = LOCAL_SYMTABLES[class_name][method_name];
    for(SymTable::iterator itr = local_symtable.begin(); itr != local_symtable.end(); ++itr){
        if(itr->second[0][0] != '*'){
            C.push_back("obj_" + itr->second[1] + " " + VAR_PREFIX + itr->first + ";");
        }
    }
}

void local_variable_declarations_method(string class_name, string method_name, set<string> args, SymTable local_symtable){
    //SymTable local_symtable = LOCAL_SYMTABLES[class_name][method_name];
    for(SymTable::iterator itr = local_symtable.begin(); itr != local_symtable.end(); ++itr){
        set<string>::iterator itr_f = args.find(itr->first);
    	bool not_found = (itr_f == args.end());
        if(itr->second[0][0] != '*' && itr->second[0][0] != '$' && itr->second[0] != method_name && itr->first != "this" && not_found){
            C.push_back("obj_" + itr->second[1] + " " + VAR_PREFIX + itr->first + ";");
        }
    }
}

void local_variable_declarations_branch(string class_name, string method_name, SymTable local_symtable, SymTable parent_symtable){
    for(SymTable::iterator itr = local_symtable.begin(); itr != local_symtable.end(); ++itr){
		bool not_found = true;
		for(SymTable::iterator itr2 = parent_symtable.begin(); itr2 != parent_symtable.end(); ++itr2){
			if(itr->first == itr2->first){
				not_found = false;
			}
		}
        if(itr->second[0][0] != '*' && itr->second[0][0] != '$' && itr->second[0] != method_name && itr->first != "this" && not_found){
            C.push_back("obj_" + itr->second[1] + " " + VAR_PREFIX + itr->first + ";");
        }
    }
}

void struct_variable_declarations(string class_name, string parent_name){
    SymTable struct_symtable = SymTables[class_name];
    SymTable parent_symtable = SymTables[parent_name];
    for(SymTable::iterator itr = parent_symtable.begin(); itr != parent_symtable.end(); ++itr){
        if(itr->second[1][0] != '*'){
            C.push_back("obj_" + itr->second[1] + " " + VAR_PREFIX + itr->first + ";");
        }
    }
    for(SymTable::iterator itr = struct_symtable.begin(); itr != struct_symtable.end(); ++itr){
        bool not_found = true;
        for(SymTable::iterator itr2 = parent_symtable.begin(); itr2 != parent_symtable.end(); ++itr2){
            if(itr->first == itr2->first){
                not_found = false;
            }
        }
        if(itr->second[1][0] != '*' && not_found){
            C.push_back("obj_" + itr->second[1] + " " + VAR_PREFIX + itr->first + ";");
        }
    }
}

void method_declarations(string class_name){
    VTable v = VTABLE_MAP[class_name];
    list<string> con_args = v[0].second;
    string con_arg_string = "(";
    int con_arg_count = 0;
    for(list<string>::iterator itr2 = con_args.begin(); itr2 != con_args.end(); ++itr2){
        con_arg_string = con_arg_string + " obj_" + *itr2 + ",";
        con_arg_count++;
    }
    if(con_arg_count > 0){
        con_arg_string.pop_back();
    }
    con_arg_string = con_arg_string + " )";
    C.push_back("obj_" + class_name + " (*" + "constructor" + ") " + con_arg_string + ";");
    int method_num = 1;
    for(VTable::iterator itr = v.begin() + 1; itr != v.end(); ++itr){
        string method_name = itr->first;
        list<string> args = itr->second;
        string arg_string = "( obj_" + IMPLIED_ARGUMENT[class_name][method_num].second.front() + ",";
        for(list<string>::iterator itr2 = args.begin(); itr2 != args.end(); ++itr2){
            arg_string = arg_string + " obj_" + *itr2 + ",";
        }
        arg_string.pop_back();
        arg_string = arg_string + " )";
        string return_type = RT_MAP[class_name][method_name];
        C.push_back("obj_" + return_type + " (*" + method_name + ") " + arg_string + ";");
        method_num++;
    }
}

void method_declarations_inst(string class_name){
    VTable v = VTABLE_MAP[class_name];
    C.push_back("new_" + class_name + ",");
    int method_num = 1;
    int last_entry = v.size();
    for(VTable::iterator itr = v.begin() + 1; itr != v.end(); ++itr){
        string method_name = itr->first;
        string ia = IMPLIED_ARGUMENT[class_name][method_num].second.front();
        if(method_num < last_entry - 1){
            C.push_back(ia + "_method_" + method_name + ",");
        }
        else{
            C.push_back(ia + "_method_" + method_name);
        }
        method_num++;
    }
}


// LCA functions

// builds a path of inheritance from r to t
//   returns true on success, else false
bool make_path(string r, string t, vector<string> &path, map< string, list<string> > cg){

	// put r on the path
	path.push_back(r);

	// check if we're done
	if(r == t){
		return true;
	}

	// try to find r in the class graph
	map< string, list<string> >::iterator itr_f = cg.find(r);
	if(itr_f == cg.end()){
		path.pop_back();
		return false;
	}

	// search down the graph
	bool found_it = false;
	for(list<string>::iterator itr = cg[r].begin(); itr != cg[r].end(); ++itr){
		found_it = make_path(*itr, t, path, cg) || found_it;
	}

	if(found_it){
		return true;
	}

	// didn't find it
	path.pop_back();
	return false;

}

string find_lca(string s1, string s2, map< string, list<string> > cg){

	// the fake class "*ERROR" inherits from everything, so the lca of *ERROR and x is always x
	if(s1 == "*ERROR"){
		return s2;
	}
	if(s2 == "*ERROR"){
		return s1;
	}

	// find paths from Obj to s1 and s2
	vector<string> path1, path2;
	bool res1 = make_path("Obj", s1, path1, cg);
	bool res2 = make_path("Obj", s2, path2, cg);

	// cout << endl;
	// cout << "here is path1: " << endl;
	// for(int i=0; i < path1.size(); i++){
	// 	cout << path1[i] << endl;
	// }
	//
	// cout << endl;
	// cout << "here is path2: " << endl;
	// for(int i=0; i < path2.size(); i++){
	// 	cout << path2[i] << endl;
	// }

    //note: probably want to just print this to cerr and return a error string so that our type check methods
    //      that call this don't bug out if they hit one of these cases
	if( !res1 ){
		LOG.insert("Debug", -1, "Warning! s1 not in class graph: " + s1);
        return "*ERROR";
	}
	if( !res2 ){
		LOG.insert("Debug", -1, "Warning! s2 not in class graph: " + s2);
        return "*ERROR";
	}

	// the lca is where the paths differ
	int idx;
	for(idx = 0; idx < path1.size() && idx < path2.size(); idx++){
		if(path1[idx] != path2[idx]){
			break;
		}
	}

	return path1[idx-1];
}


// returns true if s1 is a subclass of s2
bool is_subclass(string s1, string s2, map< string, list<string> > cg){
    return find_lca(s1, s2, cg) == s2;
}


// build the map from class name to vtable
// result goes into global variable VTABLE_MAP
VTable build_vtable(string c, VTable parent_vt){
    // Initialize variables
	VTable res = parent_vt;
	int table_size = res.size();
    list<string> empty_arg_types;
    list<string> class_name_list;
    class_name_list.push_back(c);

    // search through all classes
    list<class_node *> classes = *(root->classes);
	for(list<class_node *>::iterator itr = classes.begin(); itr != classes.end(); ++itr){
		string class_name = (*itr)->signature->class_name;
		if(class_name == c){
            // Add class constructor to vtable in first slot
            list<string> cons_arg_types;
            for(list<formal_arg_node *>::iterator formal_itr =  ((*itr)->signature->args)->begin(); formal_itr != ((*itr)->signature->args)->end(); ++formal_itr){
                cons_arg_types.push_back((*formal_itr)->value);
            }
            res[0] = make_pair(class_name, cons_arg_types);
            IMPLIED_ARGUMENT[c][0] = make_pair(class_name, empty_arg_types);

            // Add class methods to its vtable
			for(list<method_node *>::iterator itr2 = ((*itr)->body->mthds)->begin(); itr2 != ((*itr)->body->mthds)->end(); ++itr2){
                // Pull out args for current method
				list<string> arg_types;
				for(list<formal_arg_node *>::iterator itr3 = ((*itr2)->args)->begin(); itr3 != ((*itr2)->args)->end(); ++itr3){
					arg_types.push_back((*itr3)->value);
				}

                // Pull out ident for current method
				string method_name = (*itr2)->name;
				bool inserted = false;

                // Check superclass vtable to see if method already exists
				for(int i=1; i < table_size; i++){
					if(method_name == res[i].first){
						res[i] = make_pair(method_name, arg_types);
                        IMPLIED_ARGUMENT[c][i] = make_pair(method_name, class_name_list);
						inserted = true;
						break;
					}
				}
                // If it doesn't, add it
				if(!inserted){
					res.push_back(make_pair(method_name, arg_types));
                    IMPLIED_ARGUMENT[c].push_back(make_pair(method_name, class_name_list));
				}

                // Also add its return type to the ReturnTypeTable for the class
				RT_MAP[class_name][method_name] = (*itr2)->return_type;
			}

		}
	}

    // if the class is String, update it with builtin methods
    if(c == "String"){
        list<string> str_constructor_types;
        res[0] = make_pair("String", str_constructor_types);
        IMPLIED_ARGUMENT[c][0] = make_pair("String", empty_arg_types);

        list<string> str_plus_types;
    	str_plus_types.push_back("String");
        res.push_back(make_pair("LESS", str_plus_types));
    	res.push_back(make_pair("PLUS", str_plus_types));
        IMPLIED_ARGUMENT[c].push_back(make_pair("LESS", class_name_list));
        IMPLIED_ARGUMENT[c].push_back(make_pair("PLUS", class_name_list));

        // also need to set implied argument of STR, PRINT, and EQUALS methods to String
        IMPLIED_ARGUMENT[c][1] = make_pair("STR", class_name_list);
        IMPLIED_ARGUMENT[c][2] = make_pair("PRINT", class_name_list);
        IMPLIED_ARGUMENT[c][3] = make_pair("EQUALS", class_name_list);


    	RT_MAP["String"]["PLUS"] = "String";
    }

    // if the class is Int, update it with builtin methods
    if(c == "Int"){

        list<string> int_constructor_types;
        res[0] = make_pair("Int", int_constructor_types);
        IMPLIED_ARGUMENT[c][0] = make_pair("Int", empty_arg_types);
        IMPLIED_ARGUMENT[c][1] = make_pair("STR", class_name_list);
        IMPLIED_ARGUMENT[c][3] = make_pair("EQUALS", class_name_list);

        list<string> int_relation_types;
    	int_relation_types.push_back("Int");

        res.push_back(make_pair("LESS", int_relation_types));
    	res.push_back(make_pair("PLUS", int_relation_types));
        res.push_back(make_pair("MINUS", int_relation_types));
        res.push_back(make_pair("TIMES", int_relation_types));
        res.push_back(make_pair("DIVIDE", int_relation_types));
        res.push_back(make_pair("ATMOST", int_relation_types));
        res.push_back(make_pair("ATLEAST", int_relation_types));
        res.push_back(make_pair("MORE", int_relation_types));

        IMPLIED_ARGUMENT[c].push_back(make_pair("LESS", class_name_list));
        IMPLIED_ARGUMENT[c].push_back(make_pair("PLUS", class_name_list));
        IMPLIED_ARGUMENT[c].push_back(make_pair("MINUS", class_name_list));
        IMPLIED_ARGUMENT[c].push_back(make_pair("TIMES", class_name_list));
        IMPLIED_ARGUMENT[c].push_back(make_pair("DIVIDE", class_name_list));
        IMPLIED_ARGUMENT[c].push_back(make_pair("ATMOST", class_name_list));
        IMPLIED_ARGUMENT[c].push_back(make_pair("ATLEAST", class_name_list));
        IMPLIED_ARGUMENT[c].push_back(make_pair("MORE", class_name_list));

    	RT_MAP["Int"]["PLUS"] = "Int";
        RT_MAP["Int"]["MINUS"] = "Int";
        RT_MAP["Int"]["TIMES"] = "Int";
        RT_MAP["Int"]["DIVIDE"] = "Int";
        RT_MAP["Int"]["ATMOST"] = "Boolean";
        RT_MAP["Int"]["ATLEAST"] = "Boolean";
        RT_MAP["Int"]["LESS"] = "Boolean";
        RT_MAP["Int"]["MORE"] = "Boolean";
    }

    // if the class is Boolean, update it with builtin methods
    if(c == "Boolean"){

        list<string> bool_constructor_types;
        res[0] = make_pair("Boolean", bool_constructor_types);
        IMPLIED_ARGUMENT[c][0] = make_pair("Boolean", empty_arg_types);
        IMPLIED_ARGUMENT[c][1] = make_pair("STR", class_name_list);
    }

    // if the class is Nothing, update it with builtin methods
    if(c == "Nothing"){

        list<string> nothing_constructor_types;
        res[0] = make_pair("Nothing", nothing_constructor_types);
        IMPLIED_ARGUMENT[c][0] = make_pair("Nothing", empty_arg_types);
        IMPLIED_ARGUMENT[c][1] = make_pair("STR", class_name_list);
    }

	return res;
}

void build_vtable_map_recursive(map<string, list<string> > cg, string r, VTable parent_vt, string parent){
	// cout << "building table for " << r << " from parent " << parent << endl;
	RT_MAP[r] = RT_MAP[parent];
    IMPLIED_ARGUMENT[r] = IMPLIED_ARGUMENT[parent];
	VTable r_vtable = build_vtable(r, parent_vt);
	VTABLE_MAP[r] = r_vtable;
	for(list<string>::iterator itr = cg[r].begin(); itr != cg[r].end(); ++itr){
		build_vtable_map_recursive(cg, *itr, r_vtable, r);
	}
	return;
}

void build_vtable_map(map<string, list<string> > cg){

    // create the Obj vtable and update return types
	VTable obj_vtable;
    VTable implied_argument_vtable;

	list<string> obj_equals_types;
	obj_equals_types.push_back("Obj");
	list<string> obj_print_types;
	list<string> obj_str_types;
    list<string> obj_constructor_types;
    obj_vtable.push_back(make_pair("Obj", obj_constructor_types));
    obj_vtable.push_back(make_pair("STR", obj_str_types));
	obj_vtable.push_back(make_pair("PRINT", obj_print_types));
    obj_vtable.push_back(make_pair("EQUALS", obj_equals_types));

    list<string> obj_implied_types;
	obj_implied_types.push_back("Obj");
    list<string> obj_implied_empty;
    implied_argument_vtable.push_back(make_pair("Obj", obj_implied_empty));
    implied_argument_vtable.push_back(make_pair("STR", obj_implied_types));
    implied_argument_vtable.push_back(make_pair("PRINT", obj_implied_types));
	implied_argument_vtable.push_back(make_pair("EQUALS", obj_implied_types));

	VTABLE_MAP["Obj"] = obj_vtable;
    IMPLIED_ARGUMENT["Obj"] = implied_argument_vtable;

	RT_MAP["Obj"]["EQUALS"] = "Boolean";
	RT_MAP["Obj"]["PRINT"] = "Obj";
	RT_MAP["Obj"]["STR"] = "String";

	for(list<string>::iterator itr = cg["Obj"].begin(); itr != cg["Obj"].end(); ++itr){
		build_vtable_map_recursive(cg, *itr, obj_vtable, "Obj");
	}
	return;
}

// print vtable
void print_vtable(string c){
    if(!LOG.print_vt){
        return;
    }
	VTable vt = VTABLE_MAP[c];
    cerr << "------------------------------------------------------------------" << endl;
    cerr << "Method Name:         | Args:" << endl;
    cerr << "------------------------------------------------------------------" << endl;
	for(vector< pair< string, list<string> > >::iterator itr = vt.begin(); itr != vt.end(); ++itr){
		cerr << setw(20) << itr->first << " | ";
		for(list<string>::iterator itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2){
			cerr << *itr2 << "  ";
		}
        cerr << endl;
	}
    cerr << "------------------------------------------------------------------" << endl;
}

// check VTABLE_MAP
void check_vtable_map(void){
    if(!LOG.print_vt){
        return;
    }
	cout << endl;
	cout << "Checking VTable Map:" << endl;
	for(set<string>::iterator itr = CLASSES_FOUND.begin(); itr != CLASSES_FOUND.end(); ++itr){
		cerr << "Class " << *itr << ":" << endl;
		print_vtable(*itr);
        cerr << endl;
	}
}

// check RT_MAP
void check_rt_map(void){
	cerr << "Checking Return Type Map:" << endl;
	for(set<string>::iterator itr = CLASSES_FOUND.begin(); itr != CLASSES_FOUND.end(); ++itr){
		map<string, string> rtm = RT_MAP[*itr];
		cerr << *itr << ":" << endl;
        cerr << "-------------------------------------------" << endl;
        cerr << "Method Name:         | Return Type:" << endl;
        cerr << "-------------------------------------------" << endl;
		for(map<string, string>::iterator itr2 = rtm.begin(); itr2 != rtm.end(); ++itr2){
			cerr << setw(20) << (*itr2).first << " | " << (*itr2).second << endl;
		}
        cerr << "-------------------------------------------" << endl;
        cerr << endl;
	}
}




// build the class hierarchy tree (represented as an adjacency list)
//   note: we imagine the class hierarchy as a directed tree rooted at "Obj", with
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
	list<string> stack;
	stack.push_back(r);
	while(!stack.empty()){
		string current = stack.back();
		// cout << "current: " << current << endl;
		stack.pop_back();

		if(closed_set.find(current) != closed_set.end()){
			MULTIPLE_SUBCLASS = current;
			return 3;  // class has two superclasses
		}

		for(list<string>::iterator itr = cg[current].begin(); itr != cg[current].end(); ++itr){
			// cout << "  neighbor: " << *itr << endl;

			if(closed_set.find(*itr) == closed_set.end()){
				stack.push_back(*itr);
			}
			else{
				list<string>::iterator f = find(stack.begin(), stack.end(), *itr);
				if(f == stack.end()){
					MULTIPLE_SUBCLASS = *itr;
					return 3;  // class has two superclasses
				}
				else{
					CLASS_CYCLE_SUPERCLASS = current;
					CLASS_CYCLE_SUBCLASS = *itr;
					return 1;  // we have found a cycle
				}
			}
		}
		closed_set.insert(current);
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
//   note: this just calls the debug method speak
void recursive_crawl(node *n){
	n->speak();
	list<node *> children = n->get_children();

	for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
		recursive_crawl(*itr);
	}

	return;
}


// crawl the AST, printing debug statements
void crawl_ast(pgm_node *r){
	recursive_crawl((node*) r);
}


// check for class constructor call
void recursive_crawl_constructors(node *n){
	if( n->type_of_node == "expr" && ((expr_node *) n)->type_of_expression == "class_instantiation"){
		CONSTRUCTOR_CALLS.insert(((class_instantiation_node *) n)->class_name);
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
	BUILTIN_CLASSES.insert("Int");
	BUILTIN_CLASSES.insert("Boolean");
	BUILTIN_CLASSES.insert("Nothing");
}


// populate the builtin values set
void populate_builtin_values(void){
    BUILTIN_VALUES["true"] = "Boolean";
    BUILTIN_VALUES["false"] = "Boolean";
    BUILTIN_VALUES["none"] = "Nothing";
}


void print_symtable(SymTable table){
    if(!LOG.print_st){
        return;
    }
    cerr << "------------------------------------------------------------------" << endl;
    cerr << "Symbol Name:         | Static Type:         | Dynamic Type:" << endl;
    cerr << "------------------------------------------------------------------" << endl;
    for(SymTable::iterator iter = table.begin(); iter != table.end(); ++iter){
        cerr << setw(20) << iter->first << " | " << setw(20) << iter->second[0] << " | " << setw(20) << iter->second[1] << endl;
    }
    cerr << "------------------------------------------------------------------" << endl;
}


// returns a symbol table that contains all the elements that exist in every symbol table in input list
SymTable get_intersection(vector< SymTable > tables){

    // Initialize intersection to first table in list
    SymTable intersect = tables[0];

    if (LOG.print_st){
        cerr << "Grabbing Intersection:" << endl;
        cerr << "Symbol Table 0" << endl;
        print_symtable(intersect);
        cerr << endl;
    }

    // iterate through tables
    //TODO: when it hits the method_name in the symtable it causes an error as method_name obviously isn't a class... need to fix that
    int size = tables.size();
    for(int i = 1; i < size; i++){
        // Search every table for each element in intersect
        // If it isn't there remove it from intersect. If it is, set the intersection's type to the LCA of both.
        SymTable tmp_intersect = intersect;
        for(SymTable::iterator iter = intersect.begin(); iter != intersect.end(); ++iter){
            // didn't find the element, remove it from intersect
            if(tables[i].find(iter->first) == tables[i].end()){
                tmp_intersect.erase(iter->first);
            }
            // found it, update its type to the LCA of intersect type and currtable type
            else{
                tmp_intersect[iter->first][1] = find_lca(tmp_intersect[iter->first][1], tables[i][iter->first][1], CLASS_GRAPH);
            }
        }
        intersect = tmp_intersect;
    }

    if(LOG.print_st){
        cerr << "Intersection:" << endl;
        print_symtable(intersect);
    }

    // Return the intersection of all symbol tables in the list
    return intersect;
}



//TODO: need the following:
//  - Something to hold all our class symtables
//  - Something to hold all method symtables (perhaps map from class ident to method symtable)
//  - Function that prints out symtable values (for debugging)
//  - Function that initializes symtables
//      - Will involve starting from Obj and doing a traversal down the class hierarchy towards the leaves
//      - At each step, initialize its symtable to the symtable of its parent, do type checking on its symbols to find conflicts, and continue
//          - note: might need to do full type inference loop on each class before we can continue down the tree
//          -       need LCA for that
//  - note: probably best to treat program as a special class that doesn't inherit from anything (not even Obj) that we do in its own seperate part
//          to capture 'global' statements


int main(int argc, char **argv) {

	// populate the builtin classes and builtin values
	populate_builtin_classes();
    populate_builtin_values();

    // initialize logging
    LOG.enable("SyntaxError");
    LOG.enable("ClassError");
    LOG.enable("TypeError");
    LOG.enable("Error");
    // LOG.enable("Debug");

	// see if there is a file, otherwise take input from stdin
	FILE *infile;
	INFILE_NAME = (char *) "stdin";
    if (argc > 1) {
        if (argc > 2) {
            int fileidx = argc-1;
            for (int i = 1; i < fileidx; i++){
                if (strcmp(argv[i], "-s") == 0) {
                    LOG.output_st();
                }
                if (strcmp(argv[i], "-v") == 0) {
                    LOG.output_vt();
                }
            }
     	    if( !(infile = fopen(argv[fileidx], "r"))){
  		    	perror(argv[fileidx]);
  		    	exit(1);
            }
		    INFILE_NAME = argv[fileidx];
            yyin = infile;
        }

        else if (argc == 2) {
            if((strcmp(argv[1],"--help") == 0) || (strcmp(argv[1],"-help") == 0) || (strcmp(argv[1], "-h") == 0)){
                cout << "Valid Flags:" << endl;
                cout << "-s: Print symbol tables" << endl;
                cout << "-v: Print virtual method tables" << endl;
                return 0;
            }
    	    if( !(infile = fopen(argv[1], "r"))){
  		    	perror(argv[1]);
  		    	exit(1);
            }
		    INFILE_NAME = argv[1];
            yyin = infile;
        }
    }

	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));

	// if everything is OK continue processing with AST
	if(num_errors == 0){

		// make the class hierarchy graph
		CLASS_GRAPH = build_class_graph(root);

		// check that the class graph is a tree with one connected component
		int class_res = check_class_graph(CLASS_GRAPH, "Obj");
		if(class_res == 0){
			// class structure is good, next check that constructor calls are valid
            get_constructor_names(root);  // stored in global CONSTRUCTOR_CALLS

            set<string> missing;
            set_difference(CONSTRUCTOR_CALLS.begin(), CONSTRUCTOR_CALLS.end(), CLASSES_FOUND.begin(), CLASSES_FOUND.end(), inserter(missing, missing.end()));
            if(!missing.empty()){
                string msg = "class definition missing, tried to construct the following undefined classes: " + *missing.begin();
                if(missing.size() > 1){
                    for(set<string>::iterator itr = next(missing.begin(),1); itr != missing.end(); ++itr){
                        msg += ", " + *itr;
                    }
                }
                LOG.insert("ClassError", -1, msg);
            }
            else{
                // class structure and constructor calls ok: proceed with type checking

                // test the lca function
                // crawl_class_graph(CLASS_GRAPH, "Obj");
                // string lca = find_lca("C2", "C4", CLASS_GRAPH);
                // cout << "LCA: " << lca << endl;

                // type checking stuff
                build_vtable_map(CLASS_GRAPH);
                check_vtable_map();
                // check_rt_map();

                root->type_check();

				// only generate code if no errors from type checking
                if(!LOG.found_errors){

    				// generated code is saved in global variable C
    				root->emit_ir_code("*ROOT", "*ROOT");

    				// generate C code file
                    ofstream outfile;
                    outfile.open(OUTFILE_NAME);
    				for(vector<string>::iterator itr = C.begin(); itr != C.end(); ++itr){
    					outfile << *itr << endl;
    				}
                    outfile.close();

                }

            }

        }
        //TODO: need to have the line numbers for the following ClassErrors
		else if(class_res == 1){
            string msg = "circular dependancy - " + CLASS_CYCLE_SUBCLASS + " extends " + CLASS_CYCLE_SUBCLASS + " which extends it or one of its descendants";
            LOG.insert("ClassError", -1, msg);
		}
		else if(class_res == 2){
			set<string> class_extends = get_class_extends(root);
			set<string> missing;
			set_difference(class_extends.begin(), class_extends.end(), CLASSES_FOUND.begin(), CLASSES_FOUND.end(), inserter(missing, missing.end()));
			string msg = "class undefined or not a descendent of Obj\nthe following classes are undefined or non-descendants:\n";
			for(set<string>::iterator itr = missing.begin(); itr != missing.end(); ++itr){
				msg += "  " + *itr + "\n";
			}
            LOG.insert("ClassError", -1, msg);
		}
		else if(class_res == 3){
			string msg = "class " + MULTIPLE_SUBCLASS + " defined multiple times";
            LOG.insert("ClassError", -1, msg);
		}

	}

    // dump the logs if we haven't already
    LOG.print_logs();

	// delete the root of the AST (which should delete the entire thing)
	if(root != NULL){
		delete root;
	}
}
