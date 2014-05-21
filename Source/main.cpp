/**
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

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "transaction_block.hpp"
#include "database_command.hpp"
#include "global_variables.hpp"
#include "common.hpp"
#include "variable_stack.hpp"

using namespace std;

namespace
{
    bool execute_command(const db_command::database_command_data&, 
            std::vector<taction_block::transaction_block_class<int> >&);
    db_command::database_command_data gcommand_input(std::istream&);
    void command_term();
    
    
    
    inline bool execute_command(const db_command::database_command_data& c,
            std::vector<taction_block::transaction_block_class<int> >& blocks)
    {
        bool success(false);
        switch(blocks.size() > 0)
        {
            case true:
            {
                switch(c.command)
                {
                    case db_command::commit:
                    {
                        for(typename std::vector<taction_block::transaction_block_class<int> >::iterator it = 
                                blocks.begin(); ((it != blocks.end()) && (blocks.size() > 0));)
                        {
                            it->commit_changes();
                            it = blocks.erase(it);
                        }
                        success = true;
                    }
                    break;
                    
                    case db_command::begin:
                    {
                        blocks.push_back(taction_block::transaction_block_class<int>(&global::vStack));
                    }
                    break;

                    case db_command::rollback:
                    {
                        blocks.pop_back();
                        success = true;
                    }
                    break;

                    default:
                    {
                        blocks.back().add_command(c);
                        blocks.back().preview_change((blocks.back().command_count() - 1));
                        success = true;
                    }
                    break;
                }
            }
            break;

            case false:
            {
                switch(c.command)
                {
                    case db_command::rollback:
                    {
                        std::cout<< "NO TRANSACTIONS\n";
                    }
                    break;
                    
                    case db_command::begin:
                    {
                        blocks.push_back(taction_block::transaction_block_class<int>(&global::vStack));
                    }
                    break;

                    default:
                    {
                        std::string temps(db_command::execute_command(c, &global::vStack));
                        if(temps.size() > 0)
                        {
                            cout<< temps<< '\n';
                        }
                        success = true;
                    }
                    break;
                }
            }
            break;

            default:
            {
            }
            break;
        }
        return success;
    }
    
    inline db_command::database_command_data gcommand_input(std::istream& in)
    {
        bool finished(false);
        db_command::database_command_data command;
        std::string temps;
        do
        {
            in>> temps;
            if(temps == "clear")
            {
                common::cls();
            }
            else if(temps == "dumpstack")
            {
                common::cls();
                std::cout<< "Stack Begin: \n\n";
                for(unsigned int x = 0; x < global::vStack.size(); x++)
                {
                    std::cout<< global::vStack[x].name<< " = "<< global::vStack[x].value<< "\n";
                }
            }
            else if(temps == "clearstack")
            {
                global::vStack.erase_all();
            }
            else
            {
                switch(global::com_names.find(temps) != global::com_names.end())
                {
                    case true:
                    {
                        command.command = global::com_names.find(temps)->second;
                        while(in.rdbuf()->in_avail() > 1)
                        {
                            command.args.push_back(std::string());
                            in>> command.args.back();
                        }
                        finished = true;
                    }
                    break;

                    case false:
                    {
                        std::cout<< "Not a command!\n";
                    }
                    break;

                    default:
                    {
                    }
                    break;
                }
            }
        }
        while(!finished);
        return command;
    }
    
    inline void command_term()
    {
        std::vector<taction_block::transaction_block_class<int> > blocks;
        db_command::database_command_data command;
        do
        {
            command = gcommand_input(std::cin);
            if(command.command != db_command::end) execute_command(command, blocks);
        }while(command.command != db_command::end);
    }
    
    
}

int main(int count, char **vec)
{
    cin.sync_with_stdio(false);
    command_term();
    return 0;
}