#include <stdlib.h>



// node class
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

// program class
class pgm {
public:
    E_node *big_sum;
    pgm(E_node *E){
        big_sum = E;
    }
};
