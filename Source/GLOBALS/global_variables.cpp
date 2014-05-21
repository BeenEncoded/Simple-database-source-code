#include <string>
#include <map>

#include "global_variables.hpp"
#include "variable_stack.hpp"
#include "database_command.hpp"

namespace global
{
    std::map<std::string, db_command::command_type> com_names = 
            db_command::retrieve_command_map<std::string, db_command::command_type>();
    
    std::map<db_command::command_type, std::string> com_types = 
            db_command::retrieve_command_map<db_command::command_type, std::string>();
    
    var_stack::stack_class<int> vStack = var_stack::stack_class<int>();
}