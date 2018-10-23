#include<iostream>
#include<string>
#include<cmath>
#include"exception.hpp"
#include"calculator.hpp"
#include<functional>

//namespace

long double Math::add_(long double a, long double b){ return a+b; }

long double Math::sbtr_(long double a, long double b){ return a-b; }

long double Math::mult_(long double a, long double b){ return a*b; }

long double Math::div_(long double a, long double b){
    if(b==0){ throw Exception("Dividing by 0!"); }
    return a/b;
}

long double Math::pow_(long double a, long double p){
    if(a<0 && p!=static_cast<int>(p)){ throw Exception("Power error!"); }
    return pow(a,p);
}

long double Math::fact_(long double a, long double b){
    if(a<0){ throw Exception("Incalculatable factorial!"); }
    if(a==0){ return 1; }
    int ia=static_cast<int>(a);
    if(a-ia!=0){ throw Exception("Incalculatable factorial!"); }
    for(unsigned i=ia-1;i>0;--i){ ia*=i; }
    return ia;
}

long double Math::pctn_(long double a, long double b){ return a*b/100; }

long double Math::log_(long double a, long double b){
    if(a<0){ throw Exception("Log error!"); }
    return log10(a);
}

long double Math::sin_(long double a, long double b){ return sin(a); }

long double Math::cos_(long double a, long double b){ return cos(a); }

long double Math::tan_(long double a, long double b){ return tan(a); }

long double Math::sinh_(long double a, long double b){ return sinh(a); }

long double Math::cosh_(long double a, long double b){ return cosh(a); }

long double Math::tanh_(long double a, long double b){ return tanh(a); }

long double Math::arcsin_(long double a, long double b){
    if(a<-1 || a>1){ throw Exception("Arcsin error!"); }
    return asin(a);
}

long double Math::arccos_(long double a, long double b){
    if(a<-1 || a>1){ throw Exception("Arccos error!"); }
    return acos(a);
}

long double Math::arctan_(long double a, long double b){ return atan(a); }

long double Math::arcsinh_(long double a, long double b){ return asinh(a); }

long double Math::arccosh_(long double a, long double b){ return acosh(a); }

long double Math::arctanh_(long double a, long double b){ return atanh(a); }

std::function<long double(long double, long double)> operation_[20]={
    &Math::log_, &Math::arcsinh_, &Math::arccosh_, &Math::arctanh_, &Math::arcsin_, 
    &Math::arccos_, &Math::arctan_, &Math::sinh_, &Math::cosh_, &Math::tanh_, 
    &Math::sin_, &Math::cos_, &Math::tan_, &Math::pow_, &Math::fact_, &Math::pctn_, 
    &Math::mult_, &Math::div_, &Math::add_, &Math::sbtr_
};

//calculator

void Calculator::set_expr(const std::string& str){
    expr=str;   size=expr.size();
}

void Calculator::init_list(const std::string& expr){
    Expression_List* list=this->get_list();
    unsigned size=expr.size();
    unsigned index=0, length=0, position=0, priority=0;
    long double value=0;
    bool pass=true;
    for(unsigned it=0;it<size;){
        length=Operation::is_opr(&expr[it],size-it);
        index=Operation::get_index(expr.substr(it,length));
        priority=Operation::get_priority(index);
        if(index==22 && pass){
            value=atof(&expr[it]);
            list->set_list(value,position,priority,index,Expression_List::create_node());
            list=list->get_next();
            pass=false;
            ++position;
        } else if(index!=22 && index!=23){
            list->set_list(0,position,priority,index,Expression_List::create_node());
            list=list->get_next();
            pass=true;
            ++position;
            it+=(length-1);
        }
        ++it;
        if(it>=size){ delete list; }
    }
}

Expression_List* Calculator::get_list(){ return &list; }

std::string Calculator::get_expr() const{ return expr; }

bool Calculator::MeMeo_test() const{
    unsigned length=Operation::is_opr(expr,size), opr_index=0, index=0;
    unsigned counter=0;
    if(length==0){ return false; }
    for(unsigned it=0;it<size;){
        if(it==0 && 
          (expr[0]==')' || expr[0]=='^' || expr[0]=='!' || 
           expr[0]=='%' || expr[0]=='*' || expr[0]=='/' ||
           (expr[size-1]!=')' && expr[size-1]!='!' && !std::isdigit(expr[size-1])))){ return false; }
        opr_index=Operation::get_index(expr.substr(it,length));
        it+=length;
        if(opr_index==0){ ++counter; } else if(opr_index==1){ --counter; }
        if(it>=size){ if(counter!=0){ return false; } break; }
        if(!(length=Operation::is_opr(&expr[it],size-it))){ return false; }
        index=Operation::get_index(expr.substr(it,length));
        if(!Operation::is_ordered(opr_index,index)){ return false; }
    }
    return true;
}

long double Calculator::calculate(){
    try{
        this->init_list(expr);
        this->get_soe();
        return this->list.get_value();
    } catch(Exception& exception){
        throw exception;
    }
}

long double Calculator::single_opr_calc(unsigned* pos, unsigned opr_pos){
    Expression_List* node=this->get_list();
    long double a, b=0;
    unsigned opr_index=0;
    try{
        if(opr_pos==pos[0]){
            for(;node->get_position()!=opr_pos;node=node->get_next());
            a=node->get_next()->get_value();
            opr_index=node->get_index();
            if(opr_index==0 || opr_index==20){ return a; }
            else if(opr_index==21){ return -1*a; }
            return operation_[opr_index-2](a,0);
        } else if(opr_pos>pos[0] && pos[1]!=opr_pos){
            for(;node->get_position()!=pos[0];node=node->get_next());
            a=node->get_value();    node=node->get_next();
            opr_index=node->get_index();    node=node->get_next();
            b=node->get_value();
            return operation_[opr_index-2](a,b);
        } else{
            for(;node->get_position()!=pos[0];node=node->get_next());
            a=node->get_value();
            opr_index=node->get_next()->get_index();
            return operation_[opr_index-2](a,0);
        }
    } catch(Exception& exception){
        throw exception;
    }
}

void Calculator::get_soe(){
    Expression_List* List=this->get_list();
    Expression_List* node=List;
    unsigned beg=0, *beg_end=&beg, opr_index=0, priority=6;
    int pos=0;    bool pass=false;    long double elem=0;
    beg_end[0]=0;
    try{
    while(priority!=0){
        elem=0;
        for(priority=6;priority>0;--priority){
            if((pos=List->search_position(priority,beg=beg_end[0]))==-1){ continue; }
            node=List;
            for(int i=0;i<pos;++i){ node=node->get_next(); }
            beg_end=List->split(node->get_index(),pos);
            if(beg_end[1]-beg_end[0]<=2){
                elem=single_opr_calc(beg_end,pos);
                if(beg_end[0]==beg-1){ ++beg_end[0]; }
                List->manage_list(elem,beg_end[0],beg_end[1]);
                beg_end[0]=0;
                ++priority; if(pass){ priority=7; } pass=false;
            } else{
                pass=true;
                beg_end[0]++; break;
            }
        }
    } } catch(Exception& exception){
        throw exception;
    }
}

void Calculator::debug_print() const{
    std::cout<<"_________\n";
    std::cout<<"Debug Print of Calculator :\n";
    std::cout<<"&list : "<<&list<<'\n';
    std::cout<<"Expression : "<<expr<<'\n';
    std::cout<<"Size : "<<size<<'\n';
}

