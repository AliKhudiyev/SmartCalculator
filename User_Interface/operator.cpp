#include"operator.hpp"
#include<iostream>

const std::string Operation::name[MAX_NB_OPR]={
    "(", ")", "log", "arcsinh", "arccosh", "arctanh",
    "arcsin", "arccos", "arctan", "sinh", "cosh", "tanh",
    "sin", "cos", "tan", "^", "!", "%", "*", "/", "+", "-", "1", "."
};

const unsigned Operation::priority[MAX_NB_OPR]={
    6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 5, 5, 4, 3, 3, 2, 2, 1, 1, 0, 0
};

const unsigned Operation::length[MAX_NB_OPR]={
    1, 1, 3, 7, 7, 7, 6, 6, 6, 4, 4, 
    4, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
const unsigned Operation::order[MAX_NB_OPR][MAX_NB_RORD]={
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 20, 21, 22},
    {1, 15, 16, 17, 18, 19, 20, 21, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {1, 16, 17, 18, 19, 20, 21, M, M, M, M, M, M, M, M, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 22, M, M},
    {1, 15, 16, 17, 18, 19, 20, 21, 22, 23, M, M, M, M, M, M, M},
    {22, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M, M}
};

unsigned Operation::get_index(const std::string& opr){
    unsigned index=0;
    for(;index<MAX_NB_OPR-1;++index){
        if(opr.compare(name[index])==0){ return index; }
    }
    if(std::isdigit(opr[0])){ return 22; }
    else if(opr[0]=='.'){ return 23; }
    return MAX_NB_OPR;
}

unsigned Operation::jump_length(unsigned index){
    return length[index];
}

unsigned Operation::get_priority(unsigned index){
    return priority[index];
}

unsigned Operation::is_opr(const std::string& str, unsigned left){
    unsigned length=0;
    for(unsigned it=0;it<MAX_NB_OPR-1;++it){
        length=jump_length(get_index(name[it]));
        if(left<length){ continue; }
        if(str.compare(0,length,name[it])==0){ return length; }
    }
    if(std::isdigit(str[0]) || str.compare(0,length,".")==0){ return 1; }
    return 0;
}

bool Operation::is_ordered(unsigned opr_index, unsigned index){
    for(unsigned i=0;i<MAX_NB_RORD;++i){
        if(order[opr_index][i]==MAX_NB_OPR){ break; }
        if(order[opr_index][i]==index){ return true; }
    }
    return false;
}
