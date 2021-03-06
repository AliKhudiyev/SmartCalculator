/* /02.10.2018
Smart Reader library to collect the user's input and then checking it.
Handles exceptions, and supports multifunctionality to respond the user in different ways if needed.
Makes easier interface for the user, so that user interaction goes with less effort.
Containing generic class and functions to support user-dependent advanced features.
DD(Declarations+Definitions) specified library.
Easily managable, changable header file. Mostly non-static behaviours to extend functionality.

V1.1 /04.10.2018
Updated:
    -goto statement reduction
    -more of exception handling, thus safe codes
    -useless function(s) elimination
    -general code reduction
    -much better dynamic user interface

V1.2 /05.10.2018
Updated:
    -new functionality to ease the transaction and processing
    -less bugs
    -more exception handling
    -better user interface(with a newly added option)

V1.3 /06.10.2018
Updated:
    -supports new features such as ability to communicate with iaos
    -supports more compability with other classes

V1.4 /23.10.2018
Updated:
    -improved class structure
    -
*/

#include<iostream>
#include<vector>
#include"exception.hpp"

#pragma once

#define BUFF_SIZE 70

template<class T>
class Vector{
    private:
    mutable std::vector<T> vect;    //holds iaos
    mutable unsigned size;          //holds size of iaos
    unsigned sys;                   //holds size of single system
    
    void insert(unsigned r_pos, unsigned c_pos) const;
    //inserts new elements in the position of (r_pos,c_pos) in 2D displayed iaos
    //it helps user to insert any missed inputs

    void modify(unsigned r_pos, unsigned c_pos) const;
    //modifies the shown element by reinitializing it

    void remove(unsigned r_pos, unsigned c_pos) const;
    //removes element(s) in case user have entered wrong input(s)

    unsigned is_ready() const;
    //checks if the given system does not contain any wrong(or i-repetitive) sub-system
    //it gives true, if it does not contain such sub-system, and false, otherwise

    void replace(std::vector<unsigned>& order);     //incomplete
    //swaps the subsystems according to order vector

    void sort(unsigned index, unsigned beg_index, unsigned end_index);     //incomplete
    //sorts the elements of vector situated at index

    unsigned get_endIndex(unsigned beg_index, unsigned index);     //incomplete
    //returns the final index where the number which occurs at beg_index occurs

    public:
    void init();
    //initializes all the private variables
    //interacts with the user directly

    void display() const;
    //displays the current vector in a 2D plane, so that the user can see his iaos more clearly

    std::vector<T>* get_vect() const;
    //vect getter

    unsigned get_size() const;
    //size getter

    unsigned get_sys() const;
    //sys getter

    void sort();    //incomple
    //sorts the whole vector

    void debug_print() const;
    //displays all elements on the purpose of testing and debugging
};

template<class T>
void Vector<T>::init(){
    int u_sys;
    unsigned r_pos, c_pos;
    T input;
    while(true){
        try{
            std::cout<<"Enter the number of variables : ";
            std::cin>>u_sys;
            if(!std::cin.good()){
                if(!std::cin.eof()){ std::cin.clear(); std::cin.ignore(BUFF_SIZE,'\n'); }
                std::cin.clear();
                throw Exception("The number of variables should be a positive integer bigger than 2!");
            } else if(u_sys<=1){
                throw Exception("The number of variables should be bigger than 2!");
            }
            this->sys=u_sys;
            break;
        } catch(Exception& exception){
            std::cerr<<exception.get_error();
        }
    }
    while(true){
        try{
            std::cout<<"Enter an input : ";
            std::cin>>input;
            if(std::cin.eof()){ break; }
            else if(!std::cin.good()){
                std::cin.clear();
                std::cin.ignore(BUFF_SIZE,'\n');
                throw Exception("Not a number!");
            }
            vect.push_back(input);
            ++size;
        } catch(Exception& exception){
            std::cerr<<exception.get_error();
        }
    }   std::cout<<'\n';    u_sys=0;
    while(true){
        try{
            if(this->size%this->sys!=0 || this->size==0){
                throw Exception("Incomplete IaOS!");
            } else if(is_ready()!=1){
                throw Exception("Repetitive input occured! - in line ",is_ready()-size);
            } else if(u_sys==4){
                break;
            } else{
                throw Exception("Press 4 to submit.");
            }
        } catch(Exception& exception){
            std::cerr<<exception.get_error();
            this->display();
            std::cout<<"1.Insert\n2.Modify\n3.Remove\n4.Done\n5.Exit\n";
            std::cin.clear();
            std::cin>>u_sys;
            if(!std::cin.good()){ u_sys=6; std::cin.clear(); std::cin.ignore(BUFF_SIZE,'\n'); }
            switch(u_sys){
                case 1:
                    while(std::cout<<"Enter a position : ", std::cin>>r_pos>>c_pos){
                        this->insert(r_pos,c_pos);
                    }
                    break;
                case 2:
                    while(std::cout<<"Enter a position : ", std::cin>>r_pos>>c_pos){
                        this->modify(r_pos,c_pos);
                    }
                    break;
                case 3:
                    while(std::cout<<"Enter a position : ", std::cin>>r_pos>>c_pos){
                        this->remove(r_pos,c_pos);
                    }
                    break;
                case 4:
                    break;
                case 5:
                    exit(0);
                default:
                    std::cerr<<"Option does not exist!\n";
                break;
            }
        }
    }
}

template<class T>
void Vector<T>::display() const{
    std::cout<<"   ";
    for(unsigned i=0;i<sys;++i){
        std::cout<<"\\"<<i<<"/\t";
    }   std::cout<<'\n';
    for(unsigned i=0;i<size;++i){
        std::cout<<i<<" | ";
        for(unsigned j=0;j<sys;++j){
            std::cout<<vect[i*sys+j]<<"\t";
            if(i*sys+j>=size-1){ i=size; break; }
        }
        std::cout<<'\n';
    }
}

template<class T>
void Vector<T>::insert(unsigned r_pos, unsigned c_pos) const{
    T input;
    typename std::vector<T>::iterator it=vect.begin()+r_pos*sys+c_pos;
    while(true){
        try{
            std::cout<<"Enter the new input : ";
            std::cin>>input;
            if(std::cin.eof()){ std::cout<<'\n'; break; }
            else if(!std::cin.good()){
                std::cin.clear();
                std::cin.ignore(BUFF_SIZE,'\n');
                throw Exception("Not a number!");
            }
            else{
                it=vect.insert(it,input)+1;
                ++size;
                this->display();
            }
        } catch(Exception& exception){
            std::cerr<<exception.get_error();
        }
    }   std::cin.clear();
}

template<class T>
void Vector<T>::modify(unsigned r_pos, unsigned c_pos) const{
    T input;
    typename std::vector<T>::iterator it=vect.begin();
    it+=static_cast<int>(r_pos*sys+c_pos);
    std::cout<<"Enter a new input : ";
    std::cin>>input;
    it=vect.erase(it);
    it=vect.insert(it,input);
}

template<class T>
void Vector<T>::remove(unsigned r_pos, unsigned c_pos) const{
    typename std::vector<T>::iterator it=vect.begin();
    it+=static_cast<int>(r_pos*sys+c_pos);
    it=vect.erase(it);
    --size;
}

template<typename T>
unsigned Vector<T>::is_ready() const{
    unsigned counter=0;
    for(unsigned it=0;it<size/sys-1;++it){
        for(unsigned i=it+1;i<size/sys;++i){
            for(unsigned s=0;s<sys-1;++s){
                if(vect[it*sys+s]==vect[i*sys+s]){ ++counter; }
            }
        if(counter==sys-1){ return size+it; }
        counter=0;
        }
    }
    return 1;
}

// template<class T>
// void Vector<T>::replace(std::vector<unsigned>& order){
//     std::vector<T> ordered_vect(size,0);
//     T tmp;
//     for(unsigned i=0;i<size/sys;++i){
//         for(unsigned j=0;j<sys;++j){
//             ordered_vect[order[i]*sys+j]=vect[i*sys+j];
//         }
//     }
// }

// template<class T>
// void Vector<T>::sort(unsigned index, unsigned beg_index, unsigned end_index){
//     unsigned row=size/sys;
//     std::vector<unsigned> order(row,0);

//     for(unsigned i=0;i<row;++i){
//         for(unsigned j=0;j<row;++j){
//             if(vect[i*sys+index]>vect[j*sys+index]){
//                 ++order[i];
//             }
//         }
//     }

//     unsigned tmp, cnt;
//     for(unsigned i=0;i<row-1;++i){
//         cnt=0;
//         for(unsigned j=i+1;j<row;++j){
//             if(order[j]==order[i]){
//                 order[k]+=(++cnt);
//             }
//         }
//     }
//     vect.replace(order);

// }

// template<class T>
// unsigned Vector<T>::get_endIndex(unsigned beg_index, unsigned index){
//     for(unsigned i=beg_index;i<size/sys;++i){
//         if(vect[beg_index*sys+index]!=vect[(i+1)*sys+index]){
//             return i+1;
//         }
//     }
//     return 0;
// }

// template<class T>
// void Vector<T>::sort(){
//     unsigned beg_index=0, end_index=size/sys;
//     while(1){
//         for(unsigned index=0;index<sys;++index){
//             vect.sort(index,beg_index,end_index);
//             end_index=vect.get_endIndex(beg_index,index);
//         }
//         beg_index=end_index;
//     }
// }

template<class T>
std::vector<T>* Vector<T>::get_vect() const{
    return &vect;
}

template<class T>
unsigned Vector<T>::get_size() const{
    return size;
}

template<class T>
unsigned Vector<T>::get_sys() const{
    return sys;
}

template<class T>
void Vector<T>::debug_print() const{
    std::cout<<"_________\n";
    std::cout<<"Debug Print:\n";
    std::cout<<"Sys : "<<sys<<'\n';
    std::cout<<"Size : "<<size<<'\n';
    std::cout<<"Vector : \n";
    display();
}
