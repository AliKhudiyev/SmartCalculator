#include<iostream>
#include"iaos.hpp"

//extern std::function<long double(long double, long double)> operation_[22];

int main(){

   Vector<long double> vect;

//   vect.init();
//   std::cout<<"Final vector:\n";
//   vect.display();

    std::string expr;//="55.82+(arctan(2!+3.785)*3^(2/1)+(7+4)*cos7)+(0-34)";
    std::cout<<"Enter a string : ";
    getline(std::cin,expr);
    Calculator C(expr);
    if(C.MeMeo_test()==0){ std::cout<<"It should be a mathematical expression!\n"; }
    else{
        try{
            long double result=C.calculate();
            std::cout<<expr<<"="<<result<<'\n';
        } catch(Exception& exception){
            std::cerr<<exception.get_error();
        }
    }

    return 0;
}