/* /23.10.2018
Header file which contains a bunch of static operators.

*/

#include<string>

#pragma once

#define MAX_NB_OPR 24
#define M MAX_NB_OPR
#define MAX_NB_RORD 17

typedef struct OPERATION{
    private:
    static const std::string name[MAX_NB_OPR];
    static const unsigned priority[MAX_NB_OPR];
    static const unsigned length[MAX_NB_OPR];
    static const unsigned order[MAX_NB_OPR][MAX_NB_RORD];
    
    public:
    static unsigned get_index(const std::string& opr);
    static unsigned jump_length(unsigned index);
    static unsigned get_priority(unsigned index);
    static unsigned is_opr(const std::string& str, unsigned left);
    static bool is_ordered(unsigned opr_index, unsigned index);
}Operation;

typedef struct EXPRESSION_LIST{
    private:
    long double value;
    unsigned position, priority, index;
    EXPRESSION_LIST* next;

    public:
    static EXPRESSION_LIST* create_node();
    void manage_list(long double value, unsigned beg_pos, unsigned end_pos);
    int search_position(unsigned priority, unsigned beg_pos);
    unsigned* split(unsigned opr_index, unsigned opr_pos);
    unsigned cp_pos(unsigned op_pos);
    void set_list(long double value, unsigned position, unsigned priority, unsigned index, EXPRESSION_LIST* next);
    long double get_value();
    unsigned get_index();
    unsigned get_position();
    unsigned get_priority();
    EXPRESSION_LIST* get_next();
    static void delete_list(EXPRESSION_LIST* beg, EXPRESSION_LIST* end);
    void debug_print();
}Expression_List;
