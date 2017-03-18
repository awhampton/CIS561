## Quack Compiler
Authors: Garrett Morrison, Andrew Hampton


### Test Programs
The /tests directory contains subdirectories:

type_checking_tests: demonstrates type errors that are caught  
code_gen_tests: demonstrates code generation for correctly written programs  
class_structure_tests: demonstrates class structure errors that are caught  
samples: given code samples  
**invalid_tests**: greatest hits from type_checking_tests, the "bad" directory  
**valid_tests**: greatest hits from code_gen_tests, the "good" directory  

The tests in **invalid_tests** and **valid_tests** showcase the compiler's capabilities. If the user is inclined toward exploring edge cases and associated novelties, the tests in the other directories can perhaps provide some amusement.


### Basic Usage
The compiler is run through an executable **quack** that takes one argument: the name of the quack source file.

For an incorrect program, errors are written to *stderr*.

For a correct program, a C file named **generated.c** is produced.

The file **generated.c** can be turned into the executable **compiled_quack** with the command **make result**.

Example:

./quack tests/code_gen_tests/math.qk  
make result  
./compiled_quack  


### Pro Usage
There is an executable script called **do_tests** that takes one argument: the name of a directory.

This script will run **quack** on each file in that directory. For each file that does not produce any compilation errors, the script will automatically compile and run the generated C code. The results are formatted for immediate consumption.

Example: ./do_tests tests/valid_tests/


### Implementation Note

The implemented compiler conforms to the quack specification in most aspects. Due to a misunderstanding of the scoping rules of the if/elif/else conditional, there is one deviation: in our implementation, each branch inherits the containing scope and is allowed to define variables local to the scope of the branch; if a variable is defined in each branch, then it is considered to be part of the containing scope.

Here are two examples that illustrate the difference.

The following quack code is allowed in our implementation. The scope of x is the branch, and its type is inferred only using statements in this local scope:

```
/* x does not appear before this point */

if(...){
    x = A();  /* the type of x is A in this branch */
}
elif(...){
    x = B();  /* the type of x is B in this branch */
}
else{
    /* no x here */
}
```

In the following quack code, the behavior of our implementation should match the intended behavior. The scope of x is the scope which contains the if/elif/else conditional and the type is inferred in this containing scope:

```
/* x does not appear before this point */

if(...){
    x = A();  /* the type of x is LCA(A,B,C,D) in EVERY branch */
}
elif(...){
    x = B();  /* the type of x is LCA(A,B,C,D) in EVERY branch */
}
else{
    x = C();  /* the type of x is LCA(A,B,C,D) in EVERY branch */
}
x = D();  /* the type of x is LCA(A,B,C,D) in the containing scope */

/* no other x assignments in the containing scope */
```

Hopefully this difference isn't too much of a departure from the intended behavior! As a benefit, the scope on the branch provides the quack programmer with a bit more flexibility.
