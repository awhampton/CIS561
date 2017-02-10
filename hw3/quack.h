#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>


using namespace std;

// node class
class node {
public:
	string type_of_node;
	string type_of_expression;
	string type_of_statement;
	string class_name;

	virtual ~node() {};
	virtual void speak() = 0;
	virtual list<node *> get_children() = 0;
};

// expression node
class expr_node : public node {
public:

	void speak(void){
		cout << "expression node: " << type_of_expression << endl;
	}

	virtual ~expr_node() {};
	virtual list<node *> get_children() = 0;
};

// statements node
class statement_node : public node {
public:

	void speak(void){
		cout << "statement node: " << type_of_statement << endl;
	}

	virtual ~statement_node() {};
	virtual list<node *> get_children() = 0;
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
};

// formal arg node
class formal_arg_node : public node {
public:
	string name;
	string value;

    formal_arg_node(string n, string v){
		type_of_node = "formal_arg";
		name = n;
		value = v;
    }

	virtual ~formal_arg_node(){}

	void speak(void){
		cout << "formal arg node" << endl;
	}

	list<node *> get_children(){
		list<node *> res;
		return res;
	}
};

// condition node
class condition_node : public node {
public:
	expr_node *expr;
	list<statement_node *>  *stmts;

    condition_node(expr_node *e, list<statement_node *> *s){
		type_of_node = "condition";
		expr = e;
		stmts = s;
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
};

// while condition node
class while_condition_node : public condition_node {
public:

    while_condition_node(expr_node *e, list<statement_node *> *s)
	: condition_node(e, s){
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
};

// assignment statement node
class assignment_node : public statement_node {
public:
	expr_node *left;
	expr_node *right;
	string left_type;

	assignment_node(expr_node *l, string lt, expr_node *r){
		left = l;
		right = r;
		left_type = lt;
		type_of_node = "statement";
		type_of_statement = "assignment";
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
};

// return statement node
class return_node : public statement_node {
public:
	expr_node *expr;
	bool has_return_expr;

	return_node(expr_node *e){
		expr = e;
		has_return_expr = true;
		type_of_node = "statement";
		type_of_statement = "return";
	}

	return_node(){
		expr = NULL;
		has_return_expr = false;
		type_of_node = "statement";
		type_of_statement = "return";
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
};

// ident expression node
class ident_node : public expr_node {
public:
	string ident_value;

	ident_node(string s){
		ident_value = s;
		type_of_node = "expr";
		type_of_expression = "ident";
	}

	virtual ~ident_node(){}

	list<node *> get_children(){
		list<node *> res;
		return res;
	}
};

// access expression node
class access_node : public expr_node {
public:
	expr_node  *expr;
	string      ident_value;

	access_node(expr_node *e, string s){
		expr = e;
		ident_value = s;
		type_of_node = "expr";
		type_of_expression = "access";
	}

	virtual ~access_node(){
		delete expr;
	}

	list<node *> get_children(){
		list<node *> res;
		res.push_back(expr);
		return res;
	}
};

// string literal expression node
class strlit_node : public expr_node {
public:
	string strlit_value;

	strlit_node(string s){
		strlit_value = s;
		type_of_node = "expr";
		type_of_expression = "string_lit";
	}

	virtual ~strlit_node(){}

	list<node *> get_children(){
		list<node *> res;
		return res;
	}
};

// int literal expression node
class intlit_node : public expr_node {
public:
	int intlit_value;

	intlit_node(int n){
		intlit_value = n;
		type_of_node = "expr";
		type_of_expression = "int_lit";
	}

	virtual ~intlit_node(){}

	list<node *> get_children(){
		list<node *> res;
		return res;
	}
};

// method call expression node
class method_call_node : public expr_node {
public:
	expr_node                *expr;
	string                    method_name;
	list<actual_arg_node *>  *args;

	method_call_node(expr_node *e, string s, list<actual_arg_node *> *a){
		expr = e;
		method_name = s;
		args = a;
		type_of_node = "expr";
		type_of_expression = "method_call";
	}

	method_call_node(expr_node *e, string s, expr_node *o){
		expr = e;
		method_name = s;
		args = new list<actual_arg_node *>();
		args->push_back(new actual_arg_node(o));
		type_of_node = "expr";
		type_of_expression = "method_call";
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
};

// class instantiation expression node
class class_instantiation_node : public expr_node {
public:
	// string                    class_name; /* moved up to node */
	list<actual_arg_node *>  *args;

	class_instantiation_node(string s, list<actual_arg_node *> *a){
		class_name = s;
		args = a;
		type_of_node = "expr";
		type_of_expression = "class_instantiation";
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
};

// and expression node
class and_node : public expr_node {
public:
	expr_node  *left;
	expr_node  *right;

	and_node(expr_node *l, expr_node *r){
		left = l;
		right = r;
		type_of_node = "expr";
		type_of_expression = "and";
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
};

// or expression node
class or_node : public expr_node {
public:
	expr_node  *left;
	expr_node  *right;

	or_node(expr_node *l, expr_node *r){
		left = l;
		right = r;
		type_of_node = "expr";
		type_of_expression = "or";
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
};

// not expression node
class not_node : public expr_node {
public:
	expr_node  *expr;

	not_node(expr_node *e){
		expr = e;
		type_of_node = "expr";
		type_of_expression = "not";
	}

	virtual ~not_node(){
		delete expr;
	}

	list<node *> get_children(){
		list<node *> res;
		res.push_back(expr);
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
		type_of_node = "method";
		name = n;
		return_type = rt;
		args = a;
		stmts = s;
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
};

// class signature node
class class_signature_node : public node {
public:
	string class_name;
	string class_extends;
	list<formal_arg_node *> *args;

    class_signature_node(string cn, string ce, list<formal_arg_node *> *a){
		type_of_node = "class_signature";
		class_name = cn;
		class_extends = ce;
		args = a;
    }

	class_signature_node(string cn, list<formal_arg_node *> *a){
		type_of_node = "class_signature";
		class_name = cn;
		class_extends = "Obj";
		args = a;
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
};
