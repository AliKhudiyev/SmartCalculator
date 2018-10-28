/* /23.10.2018
Header file which contains a bunch of static operators.

*/

#include<string>
#include"exception.hpp"

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
