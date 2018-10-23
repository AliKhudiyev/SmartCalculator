/* /05.10.2018
Small transaction unit between the user and data holders to restore the user's input.
Static mathematical operations/functions are used to define basic operations.
Contains calculator which is capable of evaluating the expression.
Upgraded with lots of new high functionalities which helps to solve complex problems.

V1.1 /09.10.2018
Updated:
    -better interaction with float numbers
    -bugs fixed

V1.2 /13.10.2018
Updated:
    -function usage optimization
    -factorial bug fixed (0!=1)
    -pre-addition/subtraction inside parantheses bug fixed ((+1)=1, (-1)=-1)
    -first coming pre-addition/subtraction bug fixed (+1=1, -1=-1)
    -exceptional cases completed + new factorial exception added

V1.3 /15.10.2018
Updated:
    -power exception bug fixed ((-2)^3=-8)
    -factorial order bug fixed (5!+3)

V1.4 /
Updated:
    -
*/

#include<cstdlib>
#include"iaos.hpp"

IaOS::IaOS(const Vector<long double>* vector){
    io=vector->get_vect();
    sys=vector->get_sys();
    size=vector->get_size();
}

IaOS::IaOS(std::fstream& file, bool OPTION){
    long double elem;
    unsigned sys=0;
    char tmp='0';
    if(OPTION==READ){
        while(file>>elem){
            if(tmp!='\n'){ file.get(tmp); ++sys; }
            io->push_back(elem);
        }
        size=io->size();
        this->sys=sys;
    } else{
        file<<function<<'\n';
    }
}

std::string& IaOS::find_function() const{
    //incompleted
}

void IaOS::init_matrix(Matrix vector){
    //incompleted
}

void IaOS::display_matrix() const{
    for(unsigned r=0;r<size/sys;++r){
        for(unsigned c=0;c<sys;++c){
            std::cout<<(*io)[r*sys+c]<<" ";
        }
        std::cout<<'\n';
    }
}

void IaOS::display_function() const{
    for(auto it=function.begin();it<function.end();++it){
        std::cout<<*it;
    }   std::cout<<'\n';
}

void IaOS::sbtr_row(unsigned r, unsigned r1){
    for(unsigned c=0;c<sys;++c){
        (*io)[r*sys+c]-=(*io)[r1*sys+c];
    }
}

void IaOS::mult_row(unsigned r, long double k){
    for(unsigned c=0;c<sys;++c){
        (*io)[r*sys+c]*=k;
    }
}

void IaOS::swap_row(unsigned r1, unsigned r2){
    for(unsigned c=0;c<sys;++c){
        long double tmp=(*io)[r1*sys+c];
        (*io)[r1*sys+c]=(*io)[r2*sys+c];
        (*io)[r2*sys+c]=tmp;
    }
}

void IaOS::sort() const{
    //incompleted
}

bool IaOS::check_d() const{
    //incompleted
}

long double IaOS::check_D() const{
    //incompleted
}

void IaOS::solve_matrix(bool SOLVE_FOR){
    //incompleted
}

std::string IaOS::get_func() const{
    return function;
}

Matrix IaOS::get_matrix() const{
    return io;
}

IaOS::~IaOS(){
    delete io;
}

void IaOS::debug_print() const{
    std::cout<<"_________\n";
    std::cout<<"Debug Print of IaOS :\n";
    std::cout<<"Function : "<<function<<'\n';
    std::cout<<"Size : "<<size<<'\n';
    std::cout<<"Sys : "<<sys<<'\n';
    std::cout<<"Matrix : \n"; display_matrix();
}
