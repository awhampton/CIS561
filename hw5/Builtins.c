/*
 * The built-in classes of Quack
 * (incomplete implementation)
 *
 * Author: Michal Young
 */
#include <stdio.h>
#include <stdlib.h>  /* Malloc lives here; might replace with gc.h    */
#include <string.h>  /* For strcpy; might replace with cords.h from gc */

#include "Builtins.h"

/* ==============
 * Obj
 * Fields: None
 * Methods:
 *    Constructor  (called after allocation)
 *    STR
 *    PRINT
 *    EQUALS
 *
 * ==============
 */

/* Constructor */
obj_Obj new_Obj(  ) {
  obj_Obj new_thing = (obj_Obj) malloc(sizeof(struct obj_Obj_struct));
  new_thing->clazz = the_class_Obj;
  return new_thing;
}

/* Obj:STR */
obj_String Obj_method_STR(obj_Obj this_in) {
  long addr = (long) this_in;
  char *rep;
  asprintf(&rep, "<Object at %ld>", addr);
  obj_String str = str_literal(rep);
  return str;
}



/* Obj:PRINT */
obj_Obj Obj_method_PRINT(obj_Obj this_in) {
  obj_String str = this_in->clazz->STR(this_in);
  fprintf(stdout, "%s", str->text);
  return this_in;
}

/* Obj:EQUALS (Note we may want to replace this_in */
obj_Boolean Obj_method_EQUALS(obj_Obj this_in, obj_Obj other) {
  if (this_in == other) {
    return lit_true;
  } else {
    return lit_false;
  }
}


/* The Obj Class (a singleton) */
struct  class_Obj_struct  the_class_Obj_struct = {
  new_Obj,     /* Constructor */
  Obj_method_STR,
  Obj_method_PRINT,
  Obj_method_EQUALS
};

class_Obj the_class_Obj = &the_class_Obj_struct;


/* ================
 * String
 * Fields:
 *    One hidden field, currently holding char*
 *    (change later to a rope for garbage collection)
 * Methods:
 *    Those of Obj, plus ordering, concatenation
 *    (Incomplete for now.)
 * ==================
 */

/* Constructor */
obj_String new_String(  ) {
  obj_String new_thing = (obj_String) malloc(sizeof(struct obj_String_struct));
  new_thing->clazz = the_class_String;
  return new_thing;
}

/* String:STR */
obj_String String_method_STR(obj_String this_in) {
  return this_in;
}

/* String:PRINT */
obj_String String_method_PRINT(obj_String this_in) {
  fprintf(stdout, "%s", this_in->text);
  return this_in;
}

/* String:EQUALS (Note we may want to replace this_in */
obj_Boolean String_method_EQUALS(obj_String this_in, obj_Obj other) {
  obj_String other_str = (obj_String) other;
  /* But is it really? */
  if (other_str->clazz != the_class_String) {
    return lit_false;
  }
  if (strcmp(this_in->text,other_str->text) == 0) {
    return lit_true;
  } else {
    return lit_false;
  }
}

/* String:LESS */
obj_Boolean String_method_LESS(obj_String this_in, obj_String other) {
    // If they're the same length
    // Check each one character by character until one is different or we're done
    if(strlen(this_in->text) == strlen(other->text)){
        int i = 0;
        for (; i < strlen(this_in->text); i++){
            char currThis = this_in->text[i];
            char currOther = other->text[i];
            
            if (currThis == currOther)
                continue;
            else if (currThis < currOther)
                return lit_true;
            else
                return lit_false;
        }
        return lit_false; //lit_true;
    }
    
    // If they aren't
    // Check until we hit the end of the smaller string or until one is different
    // If we hit the end of the smaller string without a difference, the smaller string is less
    else{
        int i = 0;
        int min = ((strlen(this_in->text) < strlen(other->text)) ? strlen(this_in->text) : strlen(other->text));
        for (; i < min; i++){
            char currThis = this_in->text[i];
            char currOther = other->text[i];
            
            if (currThis == currOther)
                continue;
            else if (currThis < currOther)
                return lit_true;
            else
                return lit_false;
        }
        return ((strlen(this_in->text) == min) ? lit_true : lit_false);
    }
}

/* String:PLUS */
obj_String String_method_PLUS(obj_String this_in, obj_String other) {
  char* concat_string = malloc((strlen(this_in->text) + strlen(other->text) + 1)*sizeof(char));
  strcpy(concat_string, this_in->text);
  strcat(concat_string, other->text);
  return str_literal(concat_string);
}

/* String:ATMOST */
obj_Boolean String_method_ATMOST(obj_String this_in, obj_String other) {
    // If they're the same length
    // Check each one character by character until one is different or we're done
    if(strlen(this_in->text) == strlen(other->text)){
        int i = 0;
        for (; i < strlen(this_in->text); i++){
            char currThis = this_in->text[i];
            char currOther = other->text[i];
            
            if (currThis == currOther)
                continue;
            else if (currThis < currOther)
                return lit_true;
            else
                return lit_false;
        }
        return lit_true;
    }
    
    // If they aren't
    // Check until we hit the end of the smaller string or until one is different
    // If we hit the end of the smaller string without a difference, the smaller string is less
    else{
        int i = 0;
        int min = ((strlen(this_in->text) < strlen(other->text)) ? strlen(this_in->text) : strlen(other->text));
        for (; i < min; i++){
            char currThis = this_in->text[i];
            char currOther = other->text[i];
            
            if (currThis == currOther)
                continue;
            else if (currThis < currOther)
                return lit_true;
            else
                return lit_false;
        }
        return ((strlen(this_in->text) == min) ? lit_true : lit_false);
    }
}

/* String:ATLEAST */
obj_Boolean String_method_ATLEAST(obj_String this_in, obj_String other) {
    // If they're the same length
    // Check each one character by character until one is different or we're done
    if(strlen(this_in->text) == strlen(other->text)){
        int i = 0;
        for (; i < strlen(this_in->text); i++){
            char currThis = this_in->text[i];
            char currOther = other->text[i];
            
            if (currThis == currOther)
                continue;
            else if (currThis > currOther)
                return lit_true;
            else
                return lit_false;
        }
        return lit_true;
    }
    
    // If they aren't
    // Check until we hit the end of the smaller string or until one is different
    // If we hit the end of the smaller string without a difference, the larger string is more
    else{
        int i = 0;
        int min = ((strlen(this_in->text) < strlen(other->text)) ? strlen(this_in->text) : strlen(other->text));
        for (; i < min; i++){
            char currThis = this_in->text[i];
            char currOther = other->text[i];
            
            if (currThis == currOther)
                continue;
            else if (currThis > currOther)
                return lit_true;
            else
                return lit_false;
        }
        return ((strlen(other->text) == min) ? lit_true : lit_false);
    }
}

/* String:MORE */
obj_Boolean String_method_MORE(obj_String this_in, obj_String other) {
    // If they're the same length
    // Check each one character by character until one is different or we're done
    if(strlen(this_in->text) == strlen(other->text)){
        int i = 0;
        for (; i < strlen(this_in->text); i++){
            char currThis = this_in->text[i];
            char currOther = other->text[i];
            
            if (currThis == currOther)
                continue;
            else if (currThis > currOther)
                return lit_true;
            else
                return lit_false;
        }
        return lit_false;
    }
    
    // If they aren't
    // Check until we hit the end of the smaller string or until one is different
    // If we hit the end of the smaller string without a difference, the larger string is more
    else{
        int i = 0;
        int min = ((strlen(this_in->text) < strlen(other->text)) ? strlen(this_in->text) : strlen(other->text));
        for (; i < min; i++){
            char currThis = this_in->text[i];
            char currOther = other->text[i];
            
            if (currThis == currOther)
                continue;
            else if (currThis > currOther)
                return lit_true;
            else
                return lit_false;
        }
        return ((strlen(other->text) == min) ? lit_true : lit_false);
    }
}

/* The String Class (a singleton) */
struct  class_String_struct  the_class_String_struct = {
  new_String,     /* Constructor */
  String_method_STR,
  String_method_PRINT,
  String_method_EQUALS,
  String_method_LESS,
  String_method_PLUS,
  String_method_ATMOST,
  String_method_ATLEAST,
  String_method_MORE
};

class_String the_class_String = &the_class_String_struct;

/*
 * Internal use function for creating String objects
 * from char*.  Use this_in to create string literals.
 */
obj_String str_literal(char *s) {
  char *rep;
  obj_String str = the_class_String->constructor();
  str->text = s;
  return str;
}

/* ================
 * Boolean
 * Fields:
 *    One hidden field, an int (0 for False, -1 for True)
 * Methods:
 *    Those of Obj
 * =================
 */
/* Constructor */
obj_Boolean new_Boolean(  ) {
  obj_Boolean new_thing = (obj_Boolean)
    malloc(sizeof(struct obj_Boolean_struct));
  new_thing->clazz = the_class_Boolean;
  return new_thing;
}

/* Boolean:STR */
obj_String Boolean_method_STR(obj_Boolean this_in) {
  if (this_in == lit_true) {
    return str_literal(strdup("true"));
  } else if (this_in == lit_false) {
    return str_literal(strdup("false"));
  } else {
    return str_literal(strdup("!!!BOGUS BOOLEAN"));
  }
}

/* Inherit Obj:EQUAL, since we have only two
 * objects of class Boolean.
 */

/* Inherit Obj:PRINT, which will call Boolean:STR */

/* The Boolean Class (a singleton) */
struct  class_Boolean_struct  the_class_Boolean_struct = {
  new_Boolean,     /* Constructor */
  Boolean_method_STR,
  Obj_method_PRINT,
  Obj_method_EQUALS
};

class_Boolean the_class_Boolean = &the_class_Boolean_struct;

/*
 * These are the only two objects of type Boolean that
 * should ever exist. The constructor just picks one of
 * them.
 */
struct obj_Boolean_struct lit_false_struct =
  { &the_class_Boolean_struct, 0 };
obj_Boolean lit_false = &lit_false_struct;
struct obj_Boolean_struct lit_true_struct =
  { &the_class_Boolean_struct, 1 };
obj_Boolean lit_true = &lit_true_struct;

/* ==============
 * Nothing (really just a singleton Obj)
 * Fields: None
 * Methods:
 *    Constructor  (called after allocation)
 *    STR
 *    PRINT
 *    EQUALS
 *
 * ==============
 */
/*  Constructor */
obj_Nothing new_Nothing(  ) {
  return nothing;
}

/* Boolean:STR */
obj_String Nothing_method_STR(obj_Nothing this_in) {
    return str_literal(strdup("<nothing>"));
}

/* Inherit Obj:EQUAL, since we have only one
 * object of class None
 */

/* Inherit Obj:PRINT, which will call Nothing:STR */

/* The Nothing Class (a singleton) */
struct  class_Nothing_struct  the_class_Nothing_struct = {
  new_Nothing,     /* Constructor */
  Nothing_method_STR,
  Obj_method_PRINT,
  Obj_method_EQUALS
};

class_Nothing the_class_Nothing = &the_class_Nothing_struct;

/*
 * this_in is the only instance of class Nothing that
 * should ever exist
 */
struct obj_Nothing_struct nothing_struct =
  { &the_class_Nothing_struct };
obj_Nothing nothing = &nothing_struct;

/* ================
 * Int
 * Fields:
 *    One hidden field, an int
 * Methods:
 *    Those of Obj
 *    PLUS
 *    LESS
 *    (add more later)
 * =================
 */

/* Constructor */
obj_Int new_Int(  ) {
  obj_Int new_thing = (obj_Int)
    malloc(sizeof(struct obj_Int_struct));
  new_thing->clazz = the_class_Int;
  new_thing->value = 0;
  return new_thing;
}

/* Int:STR */
obj_String Int_method_STR(obj_Int this_in) {
  char *rep;
  asprintf(&rep, "%d", this_in->value);
  return str_literal(rep);
}

/* Int:EQUALS */
obj_Boolean Int_method_EQUALS(obj_Int this_in, obj_Obj other) {
  obj_Int other_int = (obj_Int) other;
  /* But is it? */
  if (other_int->clazz != this_in->clazz) {
    return lit_false;
  }
  if (this_in->value != other_int->value) {
    return lit_false;
  }
  return lit_true;
}

/* Inherit Obj:PRINT, which will call Int:STR */

/* LESS (new method) */
obj_Boolean Int_method_LESS(obj_Int this_in, obj_Int other) {
  return bool_to_lit(this_in->value < other->value);
}

/* PLUS (new method) */
obj_Int Int_method_PLUS(obj_Int this_in, obj_Int other) {
  return int_literal(this_in->value + other->value);
}

/* MINUS */
obj_Int Int_method_MINUS(obj_Int this_in, obj_Int other) {
  return int_literal(this_in->value - other->value);
}

/* TIMES */
obj_Int Int_method_TIMES(obj_Int this_in, obj_Int other) {
  return int_literal(this_in->value * other->value);
}

/* DIVIDE */
obj_Int Int_method_DIVIDE(obj_Int this_in, obj_Int other) {
  return int_literal(this_in->value / other->value);
}

/* ATMOST */
obj_Boolean Int_method_ATMOST(obj_Int this_in, obj_Int other) {
  return bool_to_lit(this_in->value <= other->value);
}

/* ATLEAST */
obj_Boolean Int_method_ATLEAST(obj_Int this_in, obj_Int other) {
  return bool_to_lit(this_in->value >= other->value);
}

/* MORE */
obj_Boolean Int_method_MORE(obj_Int this_in, obj_Int other) {
  return bool_to_lit(this_in->value > other->value);
}

/* The Int Class (a singleton) */
struct  class_Int_struct  the_class_Int_struct = {
  new_Int,     /* Constructor */
  Int_method_STR,
  Obj_method_PRINT,
  Int_method_EQUALS,
  Int_method_LESS,
  Int_method_PLUS,
  Int_method_MINUS,
  Int_method_TIMES,
  Int_method_DIVIDE,
  Int_method_ATMOST,
  Int_method_ATLEAST,
  Int_method_MORE
};

class_Int the_class_Int = &the_class_Int_struct;

/* Integer literals constructor,
 * used by compiler and not otherwise available in
 * Quack programs.
 */
obj_Int int_literal(int n) {
  obj_Int boxed = new_Int();
  boxed->value = n;
  return boxed;
}

/* ===================================
 * Functions for converting c booleans 
 * to quack boolean literals
 * ===================================
 */
obj_Boolean bool_to_lit(int bool_in){
    if(bool_in)
        return lit_true;
    return lit_false;
}

obj_Boolean LIT_OR(int a, int b){
    return bool_to_lit(a || b);
}

obj_Boolean LIT_AND(int a, int b){
    return bool_to_lit(a && b);
}

obj_Boolean LIT_NOT(int a){
    return bool_to_lit(!a);
}
