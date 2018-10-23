/* /

*/

#include"smstring.hpp"
#include"exception.hpp"

void String::set_string(const std::string& str){ this->str=str; }

void String::set_vars(const std::vector<std::string>& vars){ this->vars=vars; }

void String::set_parant(unsigned* parant){ this->parant=parant; }

void String::set_numerical(bool numerical){ this->numerical=numerical; }

std::string String::get_string(){ return this->str; }

std::string String::get_var(unsigned i){ return vars[i]; }

unsigned String::size(){ return this->size; }

unsigned String::varsize(){ return this->vars.size(); }

unsigned* String::parant(){ return this->parant; }

bool String::is_numerical(){ return this->numerical; }
