#ifndef QUACK_H
#define QUACK_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <array>
#include <vector>
#include "log.h"


using namespace std;

typedef unordered_map< string, array< string, 2 > > SymTable;
typedef vector< pair< string, list<string> > > VTable;
extern  unordered_map< string, SymTable > SymTables;
extern  map<string, list<string> > CLASS_GRAPH;
extern  map<string, VTable> VTABLE_MAP;
extern  map<string, map<string, string> > RT_MAP;
extern  DEBUG_STREAM LOG;
extern  vector< pair< int, string > > ERROR_BUFFER;
extern  bool TYPE_CHECK_AGAIN;


/////////////////////////////////
// helper functions
/////////////////////////////////
bool make_path(string r, string t, vector<string> &path, map< string, list<string> > cg);
string find_lca(string s1, string s2, map< string, list<string> > cg);
bool is_subclass(string s1, string s2, map< string, list<string> > cg);
SymTable get_intersection(vector< SymTable > tables);
void print_symtable(SymTable table);


/////////////////////////////////
// token structs
/////////////////////////////////
struct string_with_linenum {
    char *s;
    int   ln;
};

struct int_with_linenum {
    int  n;
    int  ln;
};


/////////////////////////////////
// AST node classes
/////////////////////////////////

// node class
class node {
public:
    string type_of_node;
    int    line_number;

    virtual ~node() {};
    virtual void speak() = 0;
    virtual list<node *> get_children() = 0;

    virtual string type_check(void) { return "OK"; }
    virtual string type_check(SymTable &s) { return "OK"; }
    virtual string type_check(SymTable &s, SymTable &t) { return "OK"; }
    virtual string type_check(SymTable &s, string class_name) { return "OK"; }
};

// expression node
class expr_node : public node {
public:

    string type_of_expression;

    void speak(void){
        cout << "expression node: " << type_of_expression << endl;
    }

    virtual ~expr_node() {};
    virtual list<node *> get_children() = 0;
    // virtual string type_check(/* symbol table */) = 0;
};

// statements node
class statement_node : public node {
public:

    string type_of_statement;

    void speak(void){
        cout << "statement node: " << type_of_statement << endl;
    }

    virtual ~statement_node() {};
    virtual list<node *> get_children() = 0;
    // virtual string type_check(/* symbol table */) = 0;
};


// actual arg node
class actual_arg_node : public node {
public:
    expr_node *expr;

    actual_arg_node(expr_node *e){
        type_of_node = "actual_arg";
        expr = e;
    }

    virtual ~actual_arg_node(){
        delete expr;
    }

    void speak(void){
        cout << "actual arg node" << endl;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(expr);
        return res;
    }

    string type_check(SymTable &s){
        return expr->type_check(s);
    }

    string type_check(void){
        return expr->type_check();
    }
};


// formal arg node
class formal_arg_node : public node {
public:
    string name;
    string value;  // this is the declared type

    formal_arg_node(string n, string v, int ln){
        type_of_node = "formal_arg";
        name = n;
        value = v;
        line_number = ln;
    }

    virtual ~formal_arg_node(){}

    void speak(void){
        cout << "formal arg node" << endl;
    }

    list<node *> get_children(){
        list<node *> res;
        return res;
    }

    string type_check(SymTable &s){

        // check for duplicate first! if detected, add to error list

        array<string, 2> sym_val = {value, value};
        s[name] = sym_val;

        return "OK";
    }
};


// condition node
class condition_node : public node {
public:
    expr_node *expr;
    list<statement_node *>  *stmts;

    condition_node(expr_node *e, list<statement_node *> *s, int ln){
        type_of_node = "condition";
        expr = e;
        stmts = s;
        line_number = ln;
    }

    virtual ~condition_node(){
        list<node *> children = get_children();
        for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
            delete (*itr);
        }
        delete stmts;
    }

    void speak(void){
        cout << "condition node" << endl;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(expr);
        for(list<statement_node *>::iterator itr = stmts->begin(); itr != stmts->end(); ++itr){
            res.push_back(*itr);
        }
        return res;
    }

    string type_check(SymTable &s){
        string should_be_boolean = expr->type_check(s);
        if(should_be_boolean != "Boolean"){
            // add to error list
            LOG.insert("TypeError", line_number, "non-boolean condition");
        }

        TYPE_CHECK_AGAIN = true;
        int num_type_checks = 0;
        while(TYPE_CHECK_AGAIN){
            TYPE_CHECK_AGAIN = false;
            num_type_checks++;
            string msg = "type check num: " + to_string(num_type_checks);
            LOG.insert("Debug", -1, msg);
            for(list<statement_node *>::iterator itr = stmts->begin(); itr != stmts->end(); ++itr){
                (*itr)->type_check(s);
            }
        }

        return "OK";  // don't think we actually need to return anything
    }
};


// if_elifs_else node
class if_elifs_else_node : public statement_node {
public:
    condition_node            *if_branch;
    list<condition_node *>    *elif_branches;
    list<statement_node *>    *else_stmts;

    if_elifs_else_node(condition_node *i, list<condition_node *> *elifs, list<statement_node *> *els){
        if_branch = i;
        elif_branches = elifs;
        else_stmts = els;
        type_of_node = "statement";
        type_of_statement = "if";
    }

    virtual ~if_elifs_else_node(){
        list<node *> children = get_children();
        for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
            delete (*itr);
        }
        delete elif_branches;
        delete else_stmts;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(if_branch);
        for(list<condition_node *>::iterator itr = elif_branches->begin(); itr != elif_branches->end(); ++itr){
            res.push_back(*itr);
        }
        for(list<statement_node *>::iterator itr = else_stmts->begin(); itr != else_stmts->end(); ++itr){
            res.push_back(*itr);
        }
        return res;
    }

    string type_check(SymTable &s){

        // we will accumulate symtables from each branch, then intersect them
        vector<SymTable> tables;

        // make a copy of the passed-in symtable, typecheck the branch, and save the copy in tables
        SymTable if_branch_symtable = s;
        if_branch->type_check(if_branch_symtable);
        tables.push_back(if_branch_symtable);

        for(list<condition_node *>::iterator itr = elif_branches->begin(); itr != elif_branches->end(); ++itr){
            SymTable elif_branch_symtable = s;
            (*itr)->type_check(elif_branch_symtable);
            tables.push_back(elif_branch_symtable);
        }

        // the 'else' branch is a little goofy because it's just a list of statements here
        SymTable else_branch_symtable = s;
        TYPE_CHECK_AGAIN = true;
        int num_type_checks = 0;
        while(TYPE_CHECK_AGAIN){
            TYPE_CHECK_AGAIN = false;
            num_type_checks++;
            string msg = "type check num: " + to_string(num_type_checks);
            LOG.insert("Debug", -1, msg);
            for(list<statement_node *>::iterator itr = else_stmts->begin(); itr != else_stmts->end(); ++itr){
                (*itr)->type_check(else_branch_symtable);
            }
        }
        tables.push_back(else_branch_symtable);

        // need some way to intersect the symbol tables that were generated in the branches
        // this intersection should update the types with the LCA function
        s = get_intersection(tables);

        return "OK";
    }
};


// while condition node
//   note: inherits most methods from condition_node
class while_condition_node : public condition_node {
public:

    while_condition_node(expr_node *e, list<statement_node *> *s, int ln)
    : condition_node(e, s, ln){
        type_of_node = "while_condition";
    }

    virtual ~while_condition_node(){}

    void speak(void){
        cout << "while condition node" << endl;
    }

};


// while node
class while_node : public statement_node {
public:
    while_condition_node  *wc;

    while_node(while_condition_node *w){
        wc = w;
        type_of_node = "statement";
        type_of_statement = "while";
    }

    virtual ~while_node(){
        delete wc;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(wc);
        return res;
    }

    string type_check(SymTable &s){
        // we will get a symtable from the while branch and intersect it with s
        //   i think this will correctly update both the types and the declarations
        vector<SymTable> tables;
        tables.push_back(s);

        // make a copy of the passed-in symtable, typecheck the branch, and save the copy in tables
        SymTable while_branch_symtable = s;
        wc->type_check(while_branch_symtable);
        tables.push_back(while_branch_symtable);

        // need some way to intersect the symbol tables that were generated in the branches
        // this intersection should update the types with the LCA function
        // s = get_intersection(tables);

        return "OK";
    }
};


// ident expression node
class ident_node : public expr_node {
public:
    string ident_value;

    ident_node(string s, int ln){
        ident_value = s;
        type_of_node = "expr";
        type_of_expression = "ident";
        line_number = ln;
    }

    virtual ~ident_node(){}

    list<node *> get_children(){
        list<node *> res;
        return res;
    }

    // string type_check(/* symbol table */){
    //  // return symbol_table.get_actual_type(ident_value);
    //  //   if ident_value is not found in the symbol table, add to the error list
    //  return "need to implement the symbol table";
    // }

    string type_check(SymTable &s){
        // return symbol_table.get_actual_type(ident_value);
        //   if ident_value is not found in the symbol table, add to the error list

        // try to find ident_value in the symbol table
        SymTable::iterator itr_f = s.find(ident_value);
        if(itr_f == s.end()){
            // if not found, add to the symbol table with error type "*ERROR"
            array<string, 2> sym_val = {"*ERROR", "*ERROR"};
            s[ident_value] = sym_val;
            return "*ERROR";
        }

        // else it's found, and we can return the type
        return s[ident_value][1];
    }
};


// access expression node
//   note: this represents an access of a class data member (expr).data
class access_node : public expr_node {
public:
    expr_node  *expr;
    string      ident_value;
    string      expr_type;  // after we type check the expr, store the result here

    access_node(expr_node *e, string s, int ln){
        expr = e;
        ident_value = s;
        expr_type = "*ERROR";
        type_of_node = "expr";
        type_of_expression = "access";
        line_number = ln;
    }

    virtual ~access_node(){
        delete expr;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(expr);
        return res;
    }

    // string type_check(/* symbol table */){
    //  expr_type = expr->type_check(/* symbol table */);
    //
    //  // try to find the type of ident_vlaue in the symbol table for class expr_type
    //  return "need to implement the symbol table";
    // }

    string type_check(SymTable &s){
        expr_type = expr->type_check(s);

        // try to find the type of ident_value in the symbol table for class expr_type
        unordered_map<string, SymTable>::iterator itr_f = SymTables.find(expr_type);
        if(itr_f == SymTables.end()){
            // if not found, class doesn't exist, so add to the error list
            string msg = "access node type error";
            LOG.insert("Error", line_number, msg);
            return "*ERROR";
        }

        // else try to find ident value in the table for class expr_type
        SymTable::iterator itr_f2 = SymTables[expr_type].find(ident_value);
        if(itr_f2 == SymTables[expr_type].end()){
            // if not found, class member ident_value doesn't exist, so add it to the table!
            //    note: I think this is OK, but we might end up not wanting to do this :)
            array<string, 2> sym_val = {"*ERROR", "*ERROR"};
            SymTables[expr_type][ident_value] = sym_val;
            return "*ERROR";
        }

        // else, we can return the type
        return SymTables[expr_type][ident_value][1];
    }
};


// assignment statement node
class assignment_node : public statement_node {
public:
    expr_node *left;
    expr_node *right;
    string left_type;

    assignment_node(expr_node *l, string lt, expr_node *r, int ln){
        left = l;
        right = r;
        left_type = lt;
        type_of_node = "statement";
        type_of_statement = "assignment";
        line_number = ln;
    }

    virtual ~assignment_node(){
        delete left;
        delete right;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(left);
        res.push_back(right);
        return res;
    }

    string type_check(SymTable &s){
        string left_type_eval = left->type_check(s);
        string right_type_eval = right->type_check(s);

        // bool check1 = check that declared left_type is consistent with left_type_eval
        //   left_type_eval should be a subclass of declared left_type
        bool check1 = is_subclass(left_type_eval, left_type, CLASS_GRAPH);
        if(!check1){
            // add to error list
            string msg = "assignment not consistent with declared type";
            LOG.insert("TypeError", line_number, msg);
        }

        // bool check2 = check that declared left_type is consistent with right_type_eval
        bool check2 = is_subclass(right_type_eval, left_type, CLASS_GRAPH);
        if(!check2){
            // add to error list
            string msg = "assignment not consistent with declared type";
            LOG.insert("TypeError", line_number, msg);
        }

        // bool check3 = the right side should not evaluate to type *ERROR
        bool check3 = right_type_eval != "*ERROR";
        if(!check3){
            // add to error list
            string msg = "undeclared variable";
            LOG.insert("TypeError", line_number, msg);
        }

        // update the symtable
        //   note: in evaluating the left and right type checks, the identifier on the left side
        //         should have been added to the correct table if it wasn't there already, perhaps
        //         with an error type
        //   note: right now, if a variable is declared without a type, the declared type (left_type)
        //         defaults to 'Nothing' ... this might not be what we want
        if(left->type_of_expression == "ident"){
            if(left_type_eval != find_lca(left_type_eval, right_type_eval, CLASS_GRAPH)){
                TYPE_CHECK_AGAIN = true;
            }
            array<string, 2> sym_val = {left_type, find_lca(left_type_eval, right_type_eval, CLASS_GRAPH)};
            s[((ident_node *) left)->ident_value] = sym_val;
        }

        if(left->type_of_expression == "access"){
            if(left_type_eval != find_lca(left_type_eval, right_type_eval, CLASS_GRAPH)){
                TYPE_CHECK_AGAIN = true;
            }
            array<string, 2> sym_val = {left_type, find_lca(left_type_eval, right_type_eval, CLASS_GRAPH)};
            SymTables[((access_node *) left)->expr_type][((access_node *) left)->ident_value] = sym_val;
        }

        // return something?
        return "OK";
    }
};


// bare expression statement node
class bare_expr_node : public statement_node {
public:
    expr_node *expr;

    bare_expr_node(expr_node *e){
        expr = e;
        type_of_node = "statement";
        type_of_statement = "bare_expression";
    }

    virtual ~bare_expr_node(){
        delete expr;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(expr);
        return res;
    }

    string type_check(SymTable &s){
        return expr->type_check(s);
    }
};


// return statement node
class return_node : public statement_node {
public:
    expr_node *expr;
    bool has_return_expr;
    string return_type;

    return_node(expr_node *e, int ln){
        expr = e;
        has_return_expr = true;
        return_type = "*ERROR";
        type_of_node = "statement";
        type_of_statement = "return";
        line_number = ln;
    }

    return_node(int ln){
        expr = NULL;
        has_return_expr = false;
        return_type = "Nothing";
        type_of_node = "statement";
        type_of_statement = "return";
        line_number = ln;
    }

    virtual ~return_node(){
        if(has_return_expr){
            delete expr;
        }
    }

    list<node *> get_children(){
        list<node *> res;
        if(has_return_expr){
            res.push_back(expr);
        }
        return res;
    }

    string type_check(SymTable &s){
        if(has_return_expr){
            return_type = expr->type_check(s);
        }

        // is this the right place to check that the return type matches the declared type? probably!
        //   note: does the return type just have to be a subclass of the declared type? i think so!
        bool check = is_subclass(return_type, RT_MAP[ s["this"][1] ][ s["$METHOD_NAME"][1] ], CLASS_GRAPH);
        if(!check){
            // add to error list
            string msg = "return type error";
            LOG.insert("Error", line_number, msg);
        }

        return "OK";
    }
};


// string literal expression node
class strlit_node : public expr_node {
public:
    string strlit_value;

    strlit_node(string s, int ln){
        strlit_value = s;
        type_of_node = "expr";
        type_of_expression = "string_lit";
        line_number = ln;
    }

    virtual ~strlit_node(){}

    list<node *> get_children(){
        list<node *> res;
        return res;
    }

    string type_check(SymTable &s){
        return "String";
    }
};


// int literal expression node
class intlit_node : public expr_node {
public:
    int intlit_value;

    intlit_node(int n, int ln){
        intlit_value = n;
        type_of_node = "expr";
        type_of_expression = "int_lit";
        line_number = ln;
    }

    virtual ~intlit_node(){}

    list<node *> get_children(){
        list<node *> res;
        return res;
    }

    string type_check(SymTable &s){
        return "Int";
    }
};


// method call expression node
//   note: the type of expr resolves to the calling class
class method_call_node : public expr_node {
public:
    expr_node                *expr;
    string                    method_name;
    list<actual_arg_node *>  *args;

    method_call_node(expr_node *e, string s, list<actual_arg_node *> *a, int ln){
        expr = e;
        method_name = s;
        args = a;
        type_of_node = "expr";
        type_of_expression = "method_call";
        line_number = ln;
    }

    method_call_node(expr_node *e, string s, expr_node *o, int ln){
        expr = e;
        method_name = s;
        args = new list<actual_arg_node *>();
        args->push_back(new actual_arg_node(o));
        type_of_node = "expr";
        type_of_expression = "method_call";
        line_number = ln;
    }

    virtual ~method_call_node(){
        list<node *> children = get_children();
        for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
            delete (*itr);
        }
        delete args;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(expr);
        for(list<actual_arg_node *>::iterator itr = args->begin(); itr != args->end(); ++itr){
            res.push_back(*itr);
        }
        return res;
    }

    string type_check(SymTable &s){
        string expr_type = expr->type_check(s);

        vector<string> arg_types;
        for(list<actual_arg_node *>::iterator itr = args->begin(); itr != args->end(); ++itr){
            arg_types.push_back((*itr)->type_check(s));
        }

        // first, try to find expr_type in VTABLE_MAP
        map<string, VTable>::iterator itr_f = VTABLE_MAP.find(expr_type);
        if(itr_f == VTABLE_MAP.end()){
            // if not found, class doesn't exist, so add to the error list
            string msg = "class " + expr_type + " doesn't exist";
            LOG.insert("TypeError", line_number, msg);
            return "*ERROR";
        }

        // else try to find method_name in the vtable for expr_type
        int idx = 0;
        VTable vt = VTABLE_MAP[expr_type];
        for(idx = 0; idx < vt.size(); idx++){
            if(vt[idx].first == method_name){
                break;
            }
        }

        // check if we found it
        if(idx >= vt.size()){
            // add to error list
            string msg = method_name + " is not a method of class " + expr_type;
            LOG.insert("TypeError", line_number, msg);
            return "*ERROR";
        }

        // check that the arguments are correct:

        // Make sure actual and expected arg list lengths are the same
        list<string> expected_args = vt[idx].second;
        if(expected_args.size() != arg_types.size()){
            string msg = "incorrect number of arguments for call of class " + expr_type + " method " + method_name;
            LOG.insert("TypeError", line_number, msg);
            return "*ERROR";
        }

        // compare each arg type in the received arg list against the expected arguments stored in the constructor definition
        int idx2 = 0;
        for(list<string>::iterator arg_itr = expected_args.begin(); arg_itr != expected_args.end(); ++arg_itr){
            // Check if we have an invalid constructor argument type (use LCA since a subclass of an arg is a valid input to that arg)
            string LCA = find_lca(arg_types[idx2], *arg_itr, CLASS_GRAPH);
            if(LCA != *arg_itr){
                string msg = "type of argument " + to_string(idx) + " in call of class " + expr_type + " method " + method_name + " is invalid";
                LOG.insert("TypeError", line_number, msg);
                return "*ERROR";
            }
            idx2++;
        }

        // return the return type of the method
        return RT_MAP[expr_type][method_name];
    }
};


// class instantiation expression node
class class_instantiation_node : public expr_node {
public:
    string                    class_name;
    list<actual_arg_node *>  *args;

    class_instantiation_node(string s, list<actual_arg_node *> *a, int ln){
        class_name = s;
        args = a;
        type_of_node = "expr";
        type_of_expression = "class_instantiation";
        line_number = ln;
    }

    virtual ~class_instantiation_node(){
        list<node *> children = get_children();
        for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
            delete (*itr);
        }
        delete args;
    }

    list<node *> get_children(){
        list<node *> res;
        for(list<actual_arg_node *>::iterator itr = args->begin(); itr != args->end(); ++itr){
            res.push_back(*itr);
        }
        return res;
    }

    string type_check(SymTable &s){
        // Build list of actual passed constructor arguments
        vector<string> arg_types;
        for(list<actual_arg_node *>::iterator itr = args->begin(); itr != args->end(); ++itr){
            arg_types.push_back((*itr)->type_check(s));
        }

        // Make sure actual and expected arg list lengths are the same
        list<string> expected_args = VTABLE_MAP[class_name][0].second;
        if(expected_args.size() != arg_types.size()){
            string msg = "incorrect number of arguments for call of class " + class_name + " constructor";
            LOG.insert("TypeError", line_number, msg);
            return "*ERROR";
        }

        // compare each arg type in the received arg list against the expected arguments stored in the constructor definition
        int idx = 0;
        for(list<string>::iterator arg_itr = expected_args.begin(); arg_itr != expected_args.end(); ++arg_itr){
            // Check if we have an invalid constructor argument type (use LCA since a subclass of an arg is a valid input to that arg)
            string LCA = find_lca(arg_types[idx], *arg_itr, CLASS_GRAPH);
            if(LCA != *arg_itr){
                string msg = "type of argument " + to_string(idx) + " in call of class " + class_name + " constructor is invalid";
                LOG.insert("TypeError", line_number, msg);
                return "*ERROR";
            }
            idx++;
        }

        // return the type (which for a class, is its ident)
        return class_name;
    }
};


// and expression node
class and_node : public expr_node {
public:
    expr_node  *left;
    expr_node  *right;

    and_node(expr_node *l, expr_node *r, int ln){
        left = l;
        right = r;
        type_of_node = "expr";
        type_of_expression = "and";
        line_number = ln;
    }

    virtual ~and_node(){
        delete left;
        delete right;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(left);
        res.push_back(right);
        return res;
    }

    string type_check(SymTable &s){
        string left_type = left->type_check(s);
        if(left_type != "Boolean"){
            string msg = "left type of AND is not boolean";
            LOG.insert("TypeError", line_number, msg);
            return "*ERROR";
        }

        string right_type = right->type_check(s);
        if(right_type != "Boolean"){
            string msg = "right type of AND is not boolean";
            LOG.insert("TypeError", line_number, msg);
            return "*ERROR";
        }

        return "Boolean";
    }
};


// or expression node
class or_node : public expr_node {
public:
    expr_node  *left;
    expr_node  *right;

    or_node(expr_node *l, expr_node *r, int ln){
        left = l;
        right = r;
        type_of_node = "expr";
        type_of_expression = "or";
        line_number = ln;
    }

    virtual ~or_node(){
        delete left;
        delete right;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(left);
        res.push_back(right);
        return res;
    }

    string type_check(SymTable &s){
        string left_type = left->type_check(s);
        if(left_type != "Boolean"){
            string msg = "left type of OR is not boolean";
            LOG.insert("TypeError", line_number, msg);
            return "*ERROR";
        }

        string right_type = right->type_check(s);
        if(right_type != "Boolean"){
            string msg = "right type of OR is not boolean";
            LOG.insert("TypeError", line_number, msg);
            return "*ERROR";
        }

        return "Boolean";
    }
};


// not expression node
class not_node : public expr_node {
public:
    expr_node  *expr;

    not_node(expr_node *e, int ln){
        expr = e;
        type_of_node = "expr";
        type_of_expression = "not";
        line_number = ln;
    }

    virtual ~not_node(){
        delete expr;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(expr);
        return res;
    }

    string type_check(SymTable &s){
        string expr_type = expr->type_check(s);
        if(expr_type != "Boolean"){
            string msg = "type of NOT is not boolean";
            LOG.insert("TypeError", line_number, msg);
            return "*ERROR";
        }

        return "Boolean";
    }
};


// method node
//  note: this is a method definition node
class method_node : public node {
public:
    string name;
    string return_type;
    list<formal_arg_node *> *args;
    list<statement_node *>  *stmts;

    method_node(string n, string rt, list<formal_arg_node *> *a, list<statement_node *> *s, int ln){
        type_of_node = "method";
        name = n;
        return_type = rt;
        args = a;
        stmts = s;
        line_number = ln;
    }

    virtual ~method_node(){
        list<node *> children = get_children();
        for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
            delete *itr;
        }
        delete args;
        delete stmts;
    }

    void speak(void){
        cout << "method node" << endl;
    }

    list<node *> get_children(){
        list<node *> res;
        for(list<formal_arg_node *>::iterator itr = args->begin(); itr != args->end(); ++itr){
            res.push_back(*itr);
        }
        for(list<statement_node *>::iterator itr = stmts->begin(); itr != stmts->end(); ++itr){
            res.push_back(*itr);
        }
        return res;
    }

    string type_check(SymTable &s){

        // make a symtable local to just this method
        SymTable method_symtable = s;

        // add the method name to the symtable for convenience
        array<string, 2> sym_val = {name, name};
        method_symtable["$METHOD_NAME"] = sym_val;

        // update method symbol table with formal args
        for(list<formal_arg_node *>::iterator itr = args->begin(); itr != args->end(); ++itr){
            (*itr)->type_check(method_symtable);
        }

        // type check the method's statements
        TYPE_CHECK_AGAIN = true;
        int num_type_checks = 0;
        while(TYPE_CHECK_AGAIN){
            TYPE_CHECK_AGAIN = false;
            num_type_checks++;
            string msg = "type check num: " + to_string(num_type_checks);
            LOG.insert("Debug", -1, msg);
            for(list<statement_node *>::iterator itr = stmts->begin(); itr != stmts->end(); ++itr){
                (*itr)->type_check(method_symtable);
            }
        }

        return "OK";
    }
};


// class body node
class class_body_node : public node {
public:
    list<statement_node *>  *stmts;
    list<method_node *>     *mthds;

    class_body_node(list<statement_node *> *s, list<method_node *> *m){
        type_of_node = "class_body";
        stmts = s;
        mthds = m;
    }

    virtual ~class_body_node(){
        list<node *> children = get_children();
        for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
            delete *itr;
        }
        delete stmts;
        delete mthds;
    }

    void speak(void){
        cout << "class body node" << endl;
    }

    list<node *> get_children(){
        list<node *> res;
        for(list<statement_node *>::iterator itr = stmts->begin(); itr != stmts->end(); ++itr){
            res.push_back(*itr);
        }
        for(list<method_node *>::iterator itr = mthds->begin(); itr != mthds->end(); ++itr){
            res.push_back(*itr);
        }
        return res;
    }

    string type_check(SymTable &s, string class_name){

        // these statements are the class constructor
        // we will include "this.x" fields in the symtable stored at SymTables[this_class]
        TYPE_CHECK_AGAIN = true;
        int num_type_checks = 0;
        while(TYPE_CHECK_AGAIN){
            TYPE_CHECK_AGAIN = false;
            num_type_checks++;
            string msg = "type check num: " + to_string(num_type_checks);
            LOG.insert("Debug", -1, msg);
            for(list<statement_node *>::iterator itr = stmts->begin(); itr != stmts->end(); ++itr){
                (*itr)->type_check(s);
            }
        }

        // type check the methods ... send them a blank symtable with just the class name in it
        // each method will make a copy of this symtable to start
        SymTable method_symtable_template;
        array<string, 2> sym_val = {class_name, class_name};
        method_symtable_template["this"] = sym_val;
        for(list<method_node *>::iterator itr = mthds->begin(); itr != mthds->end(); ++itr){
            (*itr)->type_check(method_symtable_template);
        }

        // is there something better to return?
        return "OK";
    }

};


// class signature node
class class_signature_node : public node {
public:
    string class_name;
    string class_extends;
    list<formal_arg_node *> *args;

    class_signature_node(string cn, string ce, list<formal_arg_node *> *a, int ln){
        type_of_node = "class_signature";
        class_name = cn;
        class_extends = ce;
        args = a;
        line_number = ln;
    }

    class_signature_node(string cn, list<formal_arg_node *> *a, int ln){
        type_of_node = "class_signature";
        class_name = cn;
        class_extends = "Obj";
        args = a;
        line_number = ln;
    }

    virtual ~class_signature_node(){
        list<node *> children = get_children();
        for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
            delete *itr;
        }
        delete args;
    }

    void speak(void){
        cout << "class signature node" << endl;
    }

    list<node *> get_children(){
        list<node *> res;
        for(list<formal_arg_node *>::iterator itr = args->begin(); itr != args->end(); ++itr){
            res.push_back(*itr);
        }
        return res;
    }

    string type_check(SymTable &s){

        // update symbol table with formal args
        for(list<formal_arg_node *>::iterator itr = args->begin(); itr != args->end(); ++itr){
            (*itr)->type_check(s);
        }

        return "OK";
    }
};


// class node
class class_node : public node {
public:
    class_signature_node *signature;
    class_body_node      *body;

    class_node(class_signature_node *cs, class_body_node *cb){
        type_of_node = "class";
        signature = cs;
        body = cb;
    }

    virtual ~class_node(){
        list<node *> children = get_children();
        for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
            delete *itr;
        }
    }

    void speak(void){
        cout << "class node" << endl;
    }

    list<node *> get_children(){
        list<node *> res;
        res.push_back(signature);
        res.push_back(body);
        return res;
    }

    string type_check(list<class_node *>* class_list){

        if(LOG.print_st){
            cerr << "received symtable from parent:" << endl;
            print_symtable(SymTables[signature->class_extends]);
            cerr << endl;
        }

        // add this class to SymTables (so we don't throw an error in the constructor)
        SymTable just_to_initialize_the_map;
        SymTables[signature->class_name] = just_to_initialize_the_map;

        // make a temp symtable that is just used for typechecking the constructor definition
        //   note: the string "this" has special meaning in this context, it refers to the class name
        SymTable class_symtable_tmp;
        array<string, 2> sym_val = {signature->class_name, signature->class_name};
        class_symtable_tmp["this"] = sym_val;

        // send class_symtable_tmp to the signature to add formal arguments
        //   note: signature->type_check takes a reference for its argument
        signature->type_check(class_symtable_tmp);

        // debug
        // for (SymTable::iterator itr = class_symtable_tmp.begin(); itr != class_symtable_tmp.end(); ++itr)
        // {
        //     cout << itr->first << ": " << itr->second[0] << " - " << itr->second[1] << endl;
        // }

        // type check the body of the class
        //    note: during this process, we will build a copy of the symtable with only the class
        //          datamembers that is saved to the global SymTables
        //    note: send the class name down for the method symbol tables
        body->type_check(class_symtable_tmp, signature->class_name);

        // debug
        if(LOG.print_st){
            cout << endl;
            cout << "local symtable for class " << signature->class_name << " in constructor" << endl;
            print_symtable(class_symtable_tmp);
            cerr << endl;
        }

        // run constructor initialization verification on all constructor variables
        for(SymTable::iterator iter = SymTables[signature->class_extends].begin(); iter != SymTables[signature->class_extends].end(); ++iter){
            // didn't find a constructor variable in the class that was expected by its superclass definition
            SymTable::iterator s_itr = SymTables[signature->class_name].find(iter->first);
            if(s_itr == SymTables[signature->class_name].end()){
                string msg = "class " + signature->class_name + " doesn't initialize variable " + iter->first + " declared by its superclass";
                LOG.insert("ClassError", signature->line_number, msg);
                //TODO: need to return an error type here maybe?
            }

            // found the constructor variable but the type was invalid
            else if((s_itr != SymTables[signature->class_name].end()) && (find_lca(s_itr->second[1], iter->second[1], CLASS_GRAPH) != iter->second[1])){
                string msg = "class " + signature->class_name + " initializes inherited variable " + iter->first + " to invalid type " + iter->second[1];
                LOG.insert("TypeError", signature->line_number, msg);
                //TODO: need to return an error type here maybe?
            }
        }

        // recurse and check all subclasses, passing our constructor symbol table to them
        for(list<string>::iterator iter = CLASS_GRAPH[signature->class_name].begin(); iter != CLASS_GRAPH[signature->class_name].end(); ++iter){
            for(list<class_node *>::iterator c_iter = class_list->begin(); c_iter != class_list->end(); ++c_iter){
                if((*c_iter)->signature->class_name == (*iter)){
                    (*c_iter)->type_check(class_list);
                }
            }
        }

        return "OK";
    }

};


// program node
class pgm_node : public node {
public:
    list<class_node *>      *classes;
    list<statement_node *>  *stmts;
    pgm_node(list<class_node *> *c, list<statement_node *> *s){
        type_of_node = "program";
        classes = c;
        stmts = s;
    }

    virtual ~pgm_node(){
        list<node *> children = get_children();
        for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
            delete *itr;
        }
        delete classes;
        delete stmts;
    }

    void speak(void){
        cout << "program node" << endl;
    }

    list<node *> get_children(){
        list<node *> res;
        for(list<class_node *>::iterator itr = classes->begin(); itr != classes->end(); ++itr){
            res.push_back(*itr);
        }
        for(list<statement_node *>::iterator itr = stmts->begin(); itr != stmts->end(); ++itr){
            res.push_back(*itr);
        }
        return res;
    }

    string type_check(/* symbol table */){

        // Begin typecheck of class hierarchy from root
        //TODO: will have to do something for checking stuff that extends a builtin class like Int or String

        //TODO: need to add Obj's builtin methods to the VTABLE_MAP
        for(list<class_node *>::iterator itr = classes->begin(); itr != classes->end(); ++itr){
            if((*itr)->signature->class_extends == "Obj"){
                (*itr)->type_check(classes);
            }
        }

        // debug: print out SymTables
        if(LOG.print_st){
            cout << endl;
            cout << "=== SymTables ===" << endl;
            for(unordered_map<string, SymTable>::iterator itr_o = SymTables.begin(); itr_o != SymTables.end(); ++itr_o){
                cout << itr_o->first << ":" << endl;
                print_symtable(itr_o->second);
                cerr << endl;
            }
        }

        // what's a good way to type check the statements in the body of the program?
        for(list<statement_node *>::iterator itr = stmts->begin(); itr != stmts->end(); ++itr){
            (*itr)->type_check(/* symbol table */);
        }

        return "OK";
    }
};

#endif  // QUACK_H
