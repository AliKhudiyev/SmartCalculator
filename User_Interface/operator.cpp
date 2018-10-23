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

Expression_List* Expression_List::create_node(){
    Expression_List* node=new Expression_List;
    node->value=0;
    node->index=0;
    node->position=0;
    node->next=nullptr;
    return node;
}

int Expression_List::search_position(unsigned priority, unsigned beg_pos){
    Expression_List* tmp=this;
    for(unsigned i=0;i<beg_pos;++i){ tmp=tmp->next; }
    for(tmp;tmp->get_priority()!=priority;tmp=tmp->next){
        if(tmp->next==nullptr || tmp->next->index==1){ return -1; }
    }
    return tmp->position;
}

unsigned* Expression_List::split(unsigned opr_index, unsigned opr_pos){
    unsigned* beg_end=new unsigned[2];
    if(opr_index==0){
        beg_end[0]=opr_pos;
        beg_end[1]=cp_pos(opr_pos);
    } else if(opr_index==Operation::get_index("!")){
        beg_end[0]=opr_pos-1;
        beg_end[1]=opr_pos;
    } else if(opr_index==Operation::get_index("^") ||
              opr_index==Operation::get_index("%") ||
              opr_index==Operation::get_index("*") ||
              opr_index==Operation::get_index("/") ||
              opr_index==Operation::get_index("+") ||
              opr_index==Operation::get_index("-")){
        beg_end[0]=(opr_pos>0)? opr_pos-1 : 0;
        beg_end[1]=opr_pos+1;
    } else{
        beg_end[0]=opr_pos;
        beg_end[1]=opr_pos+1;
    }
    return beg_end;
}

unsigned Expression_List::cp_pos(unsigned op_pos){
    Expression_List* node=this;
    for(unsigned i=0;i<=op_pos;++i){ node=node->next; }
    unsigned counter=1;
    for(;node->next!=nullptr;node=node->next){
        if(node->index==0){ ++counter; }
        else if(node->index==1){ --counter; }
        if(counter==0){ return node->position; }
    }
}

void Expression_List::set_list(long double value, unsigned position, unsigned priority, unsigned index, EXPRESSION_LIST* next){
    this->value=value;  this->position=position; this->priority=priority;   this->index=index; this->next=next;
}

long double Expression_List::get_value(){ return this->value; }

unsigned Expression_List::get_index(){ return this->index; }

unsigned Expression_List::get_position(){ return this->position; }

unsigned Expression_List::get_priority(){ return this->priority; }

Expression_List* Expression_List::get_next(){ return this->next; }

void Expression_List::delete_list(EXPRESSION_LIST* beg, EXPRESSION_LIST* end){
    Expression_List* tmp=beg;
    if(tmp!=nullptr){ for(beg;beg!=end;beg=beg->next){ tmp=beg; delete tmp; } }
}

void Expression_List::debug_print(){
    std::cout<<"_________\n";
    std::cout<<"Debug Print of List :\n";
    std::cout<<"Value : "<<this->value<<'\n';
    std::cout<<"Position : "<<this->position<<'\n';
    std::cout<<"Index : "<<this->index<<'\n';
    std::cout<<"Priority : "<<this->priority<<"\n\n";
}

void Expression_List::manage_list(long double value, unsigned beg_pos, unsigned end_pos){
    Expression_List* beg=this;
    Expression_List* end=this;
    for(unsigned i=0;i<beg_pos;++i){ beg=beg->next; end=end->next; }
    for(unsigned i=beg_pos;i<=end_pos;++i){ end=end->next; }
    Expression_List::delete_list(beg->next,end);
    beg->set_list(value,beg_pos,0,22,end);
    for(unsigned diff=end_pos-beg_pos;end!=nullptr;end=end->next){
        end->position-=diff;
    }
}
