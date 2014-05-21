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


#ifndef TRANSACTION_BLOCK_HPP_INCLUDED
#define TRANSACTION_BLOCK_HPP_INCLUDED
#include <string>
#include <iostream>
#include <vector>

#include "database_command.hpp"
#include "variable_stack.hpp"
#include "global_variables.hpp"

namespace taction_block
{
    
    /**
     * Transaction block class is used to represent a transaction block.
     */
    template<class type>
    class transaction_block_class
    {
    public:
        
        /** Initializes a transaction block with the address of a stack which it will modify. */
        explicit transaction_block_class(var_stack::stack_class<type>* s) : vstack(s),
                commands()
        {
        }
        
        ~transaction_block_class()
        {
            this->erase();
        }
        
        /** Erases the data in the class. */
        void erase()
        {
            this->commands.erase(this->commands.begin(), this->commands.end());
            this->commands.shrink_to_fit();
        }
        
        /** Adds a command to the transaction block. */
        void add_command(const db_command::database_command_data& com)
        {
            this->commands.push_back(com);
        }
        
        /** Executes all the commands on the pointed stack
         that were added to the transaction block. */
        void commit_changes()
        {
            for(auto command : this->commands) db_command::execute_command(command, this->vstack);
        }
        
        /** Displays the result of the command at index [loc], 
         calculating the effects of the previous commands. */
        void preview_change(const unsigned int& loc)
        {
            unsigned int size(this->commands.size());
            std::string temps;
            std::vector<db_command::database_command_data> counter_commands;
            if(loc < size)
            {
                for(unsigned int x = 0; ((x <= loc) && (x < size)); x++)
                {
                    counter_commands.push_back(this->find_counter_command(this->commands[x]));
                    if(counter_commands.back().command == db_command::null_com)
                    {
                        counter_commands.pop_back();
                    }
                }
                for(unsigned int x = 0; x <= loc; x++)
                {
                    temps = db_command::execute_command(this->commands[x], this->vstack);
                    if(x == loc)
                    {
                        if(temps.size() > 0)
                        {
                            std::cout<< temps<< '\n';
                        }
                    }
                }
                for(std::vector<db_command::database_command_data>::reverse_iterator it =
                        counter_commands.rbegin(); it != counter_commands.rend(); it++)
                {
                    db_command::execute_command(*it, this->vstack);
                }
            }
        }
        
        /** Returns the number of commands currently stored in the transaction. */
        unsigned int command_count() const
        {
            return this->commands.size();
        }
        
    private:
        var_stack::stack_class<type> *vstack;
        std::vector<db_command::database_command_data> commands;
        
        /** Returns a command that should reverse the effect of a command that it's
         given.  If no command counters it, such as a "GET" command, then it will
         return null_com.*/
        db_command::database_command_data find_counter_command(const db_command::database_command_data& command) const
        {
            db_command::database_command_data counter;
            counter.command = db_command::null_com;
            if(command.args.size() > 0)
            {
                switch(command.command)
                {
                    case db_command::setvar:
                    {
                        switch(this->vstack->var_exists(command.args[0]))
                        {
                            case true:
                            {
                                counter.command = db_command::setvar;
                                counter.args.push_back(command.args[0]);
                                counter.args.push_back(std::to_string(this->vstack->find_name(command.args[0]).value));
                            }
                            break;
                            
                            case false:
                            {
                                counter.command = db_command::unsetvar;
                                counter.args.push_back(command.args[0]);
                            }
                            break;
                            
                            default:
                            {
                            }
                            break;
                        }
                    }
                    break;

                    case db_command::unsetvar:
                    {
                        if(this->vstack->var_exists(command.args[0]))
                        {
                            counter.command = db_command::setvar;
                            counter.args.push_back(command.args[0]);
                            counter.args.push_back(std::to_string(this->vstack->find_name(command.args[0]).value));
                        }
                    }
                    break;

                    default:
                    {
                    }
                    break;
                }
            }
            return counter;
        }
        
    };
    
    template class transaction_block_class<int>;
    
}

#endif