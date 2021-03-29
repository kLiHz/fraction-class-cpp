#include <string>
#include <map>

#include "fraction.hpp"

using frac = fraction<long long>;

struct FracTable {
    std::map<std::string, frac> vars;
    
    FracTable() = default;
    void push(const std::string & var_name, const frac & var) {
        vars[var_name] = var;
    }
    bool has(const std::string & var_name) {
        return vars.find(var_name) != vars.end();
    }
    frac & get(const std::string & var_name) {
        auto i = vars.find(var_name);
        return i->second;
    }
};


#include <iostream>
#include <string>

#include <memory>

void trim(std::string & str) {
    auto beginning = str.find_first_not_of(" \t");
    auto ending = str.find_last_not_of(" \t");
    if (ending != std::string::npos) str = str.substr(0, ending + 1);
    if (beginning != std::string::npos) str = str.substr(beginning);
}

bool is_legal_varname(std::string & varname) {
    static std::string numbers = "0123456789";
    if (numbers.find(varname[0]) != std::string::npos) return false; 
}

bool parse(std::string & line) {
    std::string numbers = "0123456789./";
    size_t pos = 0;
    if (line[0] >= '0' || line[0] <= '9' || line[0] == '.') {
        // frac;
        auto f = frac::construct_from_str(line, &pos);
        
    }
    
}

int main() {
    FracTable frac_table;
    bool running = true;
    while (running) {
        std::cout << ">>> ";
        std::string line;
        if (!std::getline(std::cin, line)) running = false;
        trim(line);
        auto assignment_pos = line.find("=");
        if (assignment_pos != std::string::npos) {
            auto var_name = line.substr(0, assignment_pos);
            auto frac_as_str = line.substr(assignment_pos + 1);
            trim(var_name);
            auto var = frac::construct_from_str(frac_as_str);
            frac_table.push(var_name, var);
        }
        else {
            auto var_name = line.substr(0, line.find(" "));
            if (frac_table.has(var_name)) {
                std::cout << var_name << " = " << frac_table.get(var_name) << std::endl;
            } else {
                std::cout << var_name << " is not defiend. " << std::endl;
            }
        }
    }
}
