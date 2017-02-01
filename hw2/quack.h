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

class node {
public:
	virtual void speak() = 0;
	virtual list<node *> get_children() = 0;
};

// expression node
class expr_node : public node {
public:
    expr_node(){

    }

	void speak(void){
		cout << "expression node" << endl;
	}

	list<node *> get_children(){
		list<node *> res;
		return res;
	}
};

// statements node
class statement_node : public node {
public:
    statement_node(){

    }

	void speak(void){
		cout << "statement node" << endl;
	}

	list<node *> get_children(){
		list<node *> res;
		return res;
	}
};

// formal arg node
class actual_arg_node : public node {
public:
	expr_node *expr;

    actual_arg_node(expr_node *e){
		expr = e;
    }

	void speak(void){
		cout << "actual arg node" << endl;
	}

	list<node *> get_children(){
		list<node *> res;
		res.push_back(expr);
		return res;
	}
};

// formal arg node
class formal_arg_node : public node {
public:
	string name;
	string value;

    formal_arg_node(string n, string v){
		name = n;
		value = v;
    }

	void speak(void){
		cout << "formal arg node" << endl;
	}

	list<node *> get_children(){
		list<node *> res;
		return res;
	}
};

// method node
class method_node : public node {
public:
	string name;
	string return_type;
	list<formal_arg_node *> *args;
	list<statement_node *>  *stmts;

    method_node(string n, string rt, list<formal_arg_node *> *a, list<statement_node *> *s){
		name = n;
		return_type = rt;
		args = a;
		stmts = s;
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
};

// formal arg node
class class_body_node : public node {
public:
	list<statement_node *>  *stmts;
	list<method_node *>     *mthds;

    class_body_node(list<statement_node *> *s, list<method_node *> *m){
		stmts = s;
		mthds = m;
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
};

// class signature node
class class_signature_node : public node {
public:
	string class_name;
	string class_extends;
	list<formal_arg_node *> *args;

    class_signature_node(string cn, string ce, list<formal_arg_node *> *a){
		class_name = cn;
		class_extends = ce;
		args = a;
    }

	class_signature_node(string cn, list<formal_arg_node *> *a){
		class_name = cn;
		class_extends = "Obj";
		args = a;
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
};

// classes node
class class_node : public node {
public:
	class_signature_node *signature;
	class_body_node      *body;

    class_node(class_signature_node *cs, class_body_node *cb){
		signature = cs;
		body = cb;
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
};

// program node
class pgm_node : public node {
public:
    list<class_node *>      *classes;
	list<statement_node *>  *stmts;
    pgm_node(list<class_node *> *c, list<statement_node *> *s){
        classes = c;
		stmts = s;
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
};
