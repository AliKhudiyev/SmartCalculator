#include"list.hpp"
#include"operator.hpp"
#include<iostream>

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
