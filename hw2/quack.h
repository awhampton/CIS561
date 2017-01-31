#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>

using namespace std;

// node class
/*
class E_node {
public:
	int my_int;
    bool got_int;
	E_node *left;
	E_node *right;

	E_node(E_node* l, E_node* r){
		left = l;
		right = r;
        got_int = false;
	}

    E_node(int n){
        my_int = n;
        got_int = true;
    }
};
*/

// formal arg node
class formal_arg_node {
public:
	string name;
	string value;

    formal_arg_node(string n, string v){
		name = n;
		value = v;
    }
};

// class signature node
class class_signature_node {
public:
	string class_name;
	string class_extends;

    class_signature_node(string cn, string ce){
		class_name = cn;
		class_extends = ce;
    }

	class_signature_node(string cn){
		class_name = cn;
		class_extends = "Obj";
    }
};

// class body node
class class_body_node {
public:
    class_body_node(){

    }
};

// statements node
class statement_node {
public:
    statement_node(){

    }
};

// classes node
class class_node {
public:
	class_signature_node *signature;
	class_body_node      *body;

    class_node(class_signature_node *cs, class_body_node *cb){
		signature = cs;
		body = cb;
    }
};

// program node
class pgm_node {
public:
    list<class_node *>      *classes;
	list<statement_node *>  *stmts;
    pgm_node(list<class_node *> *c, list<statement_node *> *s){
        classes = c;
		stmts = s;
    }
};
