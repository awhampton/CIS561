#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <list>
#include <string>
#include <unordered_map>

using namespace std;

class DEBUG_STREAM {
    
    int num_errors = 0;
    list<string> DEBUG_BUFFER;
    unordered_map< string, bool > options;
    DEBUG_STREAM();
    
    public:
    bool print_st = false;
    bool print_vt = false;
    
    // Constructor
    DEBUG_STREAM(int n_err){
        if (n_err > 0)
            num_errors = n_err;
        options["ClassError"] = false;
        options["SyntaxError"] = false;
        options["TypeError"] = false;
        options["Error"] = false;
        options["Debug"] = false;
    }
    
    // Enable debug types
    void enable(string pname){
        if(options.find(pname) != options.end()){
            options[pname] = true;
        }
    }
    
    // Enable symbol table printing
    void output_st(void){
        print_st = true;
    }
    
    // Enable virtual method table printing
    void output_vt(void){
        print_vt = true;
    }
    
    // Dump debug buffer to output stream
    void print_logs(void){
        for(list<string>::iterator iter = DEBUG_BUFFER.begin(); iter != DEBUG_BUFFER.end(); ++iter){
            cerr << (*iter) << endl;
        }
    }
    
    // Insert log instance
    void insert(string type, int lineNum, string msg){
        if(options.find(type) == options.end()){
            cerr << "DEBUG_STREAM ERROR: invalid debug type" << endl;
            exit(1);
        }
        
        string line = "";
        if (lineNum != -1){
            line += "(line " + to_string(lineNum) + ")";
        }
        
        if(options[type] == true){
            if(num_errors == 0){
                print_logs();
                exit(0);
            }
            
            string debug_msg = type + " " + line + ": " + msg;
            DEBUG_BUFFER.push_back(debug_msg);
            
            // Don't want to count debug messages as errors against our error limit
            if(type != "Debug"){
                num_errors--;
            }
        }
    }
    
};

#endif
