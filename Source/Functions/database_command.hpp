/*
    The MIT License (MIT)

    Copyright (c) 2014 Jonathan Craig Whitlock

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
 */

#ifndef DATABASE_COMMAND_HPP_INCLUDED
#define DATABASE_COMMAND_HPP_INCLUDED
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <utility>

#include "variable_stack.hpp"

namespace db_command
{
    struct database_command_data;
    
    
    
    /** Defines a command's type. */
    enum command_type
    {
        null_com = 0,
        setvar = 1,
        getvar = 2,
        unsetvar = 3,
        numequaltovar = 4,
        end = 5,
        commit = 6,
        rollback = 7,
        begin = 8
    };
    
    
    /** contains essential type_check templates, and a function that
     retrieve_command_map uses. */
    namespace type_checks
    {
        std::vector<std::pair<db_command::command_type, std::string> > retrieve_commands();
        
        template<class type>
        struct is_command_type : std::false_type
        {
        };

        template<>
        struct is_command_type<db_command::command_type> : std::true_type
        {
        };

        template<class type>
        struct is_string_type : std::false_type
        {
        };

        template<>
        struct is_string_type<std::string> : std::true_type
        {
        };
    }
    
    
    
    /** Represents a single command. */
    struct database_command_data
    {
        command_type command = null_com;
        std::vector<std::string> args;
        
        const database_command_data& operator=(const database_command_data& d)
        {
            if(this != &d)
            {
                this->command = d.command;
                this->args = d.args;
            }
            return *this;
        }
    };
    
    
    /** the namespace limits the function's definition. */
    namespace
    {
        /** Retrieves a map of strings and command types.  This will allow
         the easy retrieval and use of commands and their corresponding
         data representations */
        template<class type1, class type2>
        std::map<type1, type2> retrieve_command_map()
        {
            using namespace type_checks;
            
            /* If you're getting an error here, then you're passing the wrong value types.  This
             function takes a string and a command_type in any order.  std::enable_if
             is used to make sure you don't use this function incorrectly! */
            return std::map<typename std::enable_if<((is_string_type<type1>::value && is_command_type<type2>::value) ||
                    (is_command_type<type1>::value && is_string_type<type2>::value)), type1>::type, 
                    typename std::enable_if<((is_string_type<type1>::value && is_command_type<type2>::value) ||
                    (is_command_type<type1>::value && is_string_type<type2>::value)), type2>::type>();
        }
        
        template<>
        std::map<command_type, std::string> retrieve_command_map<command_type, std::string>()
        {
            using namespace type_checks;

            std::vector<std::pair<command_type, std::string> > command_associations(retrieve_commands());
            std::map<command_type, std::string> coms;
            unsigned int size(command_associations.size());
            for(unsigned int x = 0; x < size; x++)
            {
                coms[command_associations[x].first] = command_associations[x].second;
            }
            return coms;
        }

        template<>
        std::map<std::string, command_type> retrieve_command_map<std::string, command_type>()
        {
            using namespace type_checks;

            std::vector<std::pair<command_type, std::string> > command_associations(retrieve_commands());
            std::map<std::string, command_type> coms;
            unsigned int size(command_associations.size());
            for(unsigned int x = 0; x < size; x++)
            {
                coms[command_associations[x].second] = command_associations[x].first;
            }
            return coms;
        }
        
        /** Executes commands that can be applied to the stack. */
        template<class type>
        std::string execute_command(const database_command_data& com, 
                var_stack::stack_class<type>* s)
        {
            using std::cout;
            
            std::string message;
            switch(com.command)
            {
                case null_com:
                {
                }
                break;
                
                case setvar:
                {
                    if(com.args.size() < 2)
                    {
                        message = "Invalid arguments";
                    }
                    if(com.args.size() >= 2)
                    {
                        s->set_var(com.args[0], std::stoi(com.args[1]));
                    }
                }
                break;
                
                case getvar:
                {
                    message = "invalid arguments";
                    if(com.args.size() > 0)
                    {
                        message.erase();
                        switch(s->var_exists(com.args[0]))
                        {
                            case true:
                            {
                                message = std::to_string(s->find_name(com.args[0]).value);
                            }
                            break;
                            
                            case false:
                            {
                                message = "NULL";
                            }
                            break;
                            
                            default:
                            {
                            }
                            break;
                        }
                    }
                }
                break;
                
                case unsetvar:
                {
                    message = "invalid arguments";
                    if(com.args.size() > 0)
                    {
                        message.erase();
                        s->remove_var(com.args[0]);
                    }
                }
                break;
                
                case numequaltovar:
                {
                    if(com.args.size() > 0)
                    {
                        message =  std::to_string(s->find_values(std::stoi(com.args[0])));
                    }
                }
                break;
                
                case end:
                case commit:
                case rollback:
                case begin:
                default:
                {
                }
                break;
            }
            return message;
        }
        
        
    }
    
}

#endif
