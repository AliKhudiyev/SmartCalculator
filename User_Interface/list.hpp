
#pragma once

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
