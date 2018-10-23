/* /
String class is for helping to work with strings easily and quickly without much effort.
It is very useful to work with function strings.
It supports high functionality with its various operators and functions.
*/

#include<string>
#include<vector>

#pragma once

#define NUMERICAL true
#define N_NUMERICAL false

//using Function = String;

class String{
    private:
    std::string str;
    std::vector<std::string> vars;
    unsigned size;
    unsigned* parant;
    bool numerical;

    public:
    String(){ }
    String(std::string& str): 
        str(str) , numerical(N_NUMERICAL) , size(str.size()) {}
    String(std::string& str, std::vector<std::string>& vars): 
        str(str) , vars(vars) , numerical(NUMERICAL) , size(str.size()) {}
    
    void set_string(const std::string& str);
    void set_vars(const std::vector<std::string>& vars);
    void set_parant(unsigned* parant);
    void set_numerical(bool numerical);
    std::string get_string();
    std::string get_var(unsigned i);
    unsigned size();
    unsigned varsize();
    unsigned* parant();
    bool is_numerical();
    
    std::string cut(int beg_pos, int end_pos);
    void compare(const String& string);
    void copy(int beg_pos, const String& string);
    void simplify();

    char operator[](unsigned i);
    std::string operator+=(const String& string);
    std::string operator-=(const String& string);
    std::string operator+(const String& string);
    std::string operator-(const String& string);
    std::string operator*=(const String& string);
    std::string operator*(const String& string);
    std::string operator=(const String& string);

    std::ostream& operator<<(const std::ostream& out);
    std::istream& operator>>(const std::istream& in);
    ~String();
};
