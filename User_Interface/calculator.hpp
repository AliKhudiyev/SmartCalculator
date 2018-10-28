/* /23.10.2018
Calculator header file which supports epxression checking and calculating

*/

//#include"operator.hpp"
#include"list.hpp"
#include"exception.hpp"

#pragma once

class Calculator{
    private:
    Expression_List list;           //
    std::string expr;               //holds mathematical expression
    unsigned size;                  //holds the size of expr

    public:
    Calculator(){}
    //default constructer if no pre-initialization is needed

    Calculator(const std::string& str): expr(str) , size(str.size()) {}
    //pre-initialization of 'expression' and its size via the constructer

    void set_expr(const std::string& str);
    //post-initialization of 'expression' string and its size

    void init_list(const std::string& expr);
    //initializes Expression_List with numerical values of expr

    Expression_List* get_list();
    //list getter

    std::string get_expr() const;
    //returs the 'expr' string for user

    bool MeMeo_test() const;
    //first, tests if the given expression only contains mathematical symbols and numbers
    //second, tests if all terms in the expression are in the right mathematical order
    //finally, gives "true" if passes through first 2 sub-tests succesfully, and "false" otherwise

    long double calculate();
    //after getting "true" from MeMeo_test this function treats the expression as a mathematical expression
    //and then calculates the expression with the help of get_soe, then returns the final result of calculation

    long double single_opr_calc(unsigned* pos, unsigned opr_index);
    //solves the expression containing only and only single operation or operator

    void get_soe();
    //non-recursive function which separates the expression into pieces that have only one operator
    //then solves all pieces, puts them together in managed order in the list
    //then repeats this process until the end, in the end only a value remains as the first element of list

    void debug_print() const;
    //displays all the variables clearly
};

namespace Math{
    long double add_(long double a, long double b);
    long double sbtr_(long double a, long double b);
    long double mult_(long double a, long double b);
    long double div_(long double a, long double b);
    long double pow_(long double a, long double p);
    long double fact_(long double a, long double b);
    long double pctn_(long double a, long double b);
    long double log_(long double a, long double b);
    long double sin_(long double a, long double b);
    long double cos_(long double a, long double b);
    long double tan_(long double a, long double b);
    long double sinh_(long double a, long double b);
    long double cosh_(long double a, long double b);
    long double tanh_(long double a, long double b);
    long double arcsin_(long double a, long double b);
    long double arccos_(long double a, long double b);
    long double arctan_(long double a, long double b);
    long double arcsinh_(long double a, long double b);
    long double arccosh_(long double a, long double b);
    long double arctanh_(long double a, long double b);
}
