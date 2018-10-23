/* /05.10.2018
IaOS library with default mathematical operations.
3 different classes for operations, numerical calculations and iaos
Contains static (and const) operations and static information about them since they are not changable.
High functionality with full of various "smart" functions.

V1.1 /09.10.2018
Updated:
    -useless functions reduction
    -bugs fixed
    -function optimization
    -goto statement reduction
    -memory optimization
*/

#include<cmath>
#include<fstream>
#include"calculator.hpp"
#include"smreader.hpp"

#pragma once

#define MAX_NB_OPR 24
#define M MAX_NB_OPR
#define MAX_NB_RORD 17

#define SOLVE_FOR_FUNCTION true
#define SOLVE_FOR_OUPUT false

#define READ true
#define WRITE false

typedef std::vector<long double>* Matrix;

class IaOS{
    private:
    mutable std::string function;   //holds function
    mutable Matrix io;              //holds iaos as numbers
    unsigned sys;                   //holds size of a single system
    unsigned size;                  //holds size of io vector
    unsigned ncsr_nb_sys;           //holds size of necessary number of systems to avoid inefficient allocations
    Calculator C;                   //holds a calculator to be able to calculate any expression

    public:
    IaOS(const Vector<long double>* vector);
    //initializes the IaOS class variables with a const 'vector' Vector<long double> class

    IaOS(std::fstream& file, bool OPTION);
    //depending on the OPTION: READ or WRITE, it either reads from file or writes to file

    std::string& find_function() const;
    //returns the appropriate 1D function for 1D 'io' matrix
    //assigns the 'function' string to the found function

    void init_matrix(Matrix matrix);
    //initializes the 'io' matrix with 'matrix' matrix

    void display_matrix() const;
    //displays all the elements of matrix
    //matrix can be either a collection of iaos of a known function
    //or a collection of iaos of an unknown function 

    void display_function() const;
    //displays the current function

    void sbtr_row(unsigned r, unsigned r1);
    //row subtraction in matrix

    void mult_row(unsigned r, long double k);
    //row multiplication in matrix

    void swap_row(unsigned r1, unsigned r2);
    //row swapping in matrix

    void sort() const;
    //sorts the io matrix from left to right(except the outputs)

    bool check_d() const;
    //

    long double check_D() const;
    //

    void solve_matrix(bool SOLVE_FOR);
    //there are 2 main types of solution: solving for function output and solving for number output

    std::string get_func() const;
    //function getter

    Matrix get_matrix() const;
    //matix getter

    ~IaOS();
    //IaOS destructer to deallocate the allocated memory

    void debug_print() const;
    //shows all the variables clearly
};
