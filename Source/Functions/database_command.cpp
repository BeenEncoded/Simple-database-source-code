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

#include <string>
#include <utility>
#include <vector>
#include <map>

#include "database_command.hpp"
#include "variable_stack.hpp"

namespace
{
}

namespace db_command
{
    namespace type_checks
    {
        std::vector<std::pair<db_command::command_type, std::string> > retrieve_commands()
        {
            using db_command::command_type;

            std::vector<std::pair<command_type, std::string> > coms;
            std::string command_names[9] = {
                "NULL",
                "SET",
                "GET",
                "UNSET",
                "NUMEQUALTO",
                "END",
                "COMMIT",
                "ROLLBACK",
                "BEGIN"
            };
            for(unsigned int x = 0; x < 9; x++)
            {
                coms.push_back(std::pair<command_type, std::string>());
                coms.back().first = (command_type)x;
                coms.back().second = command_names[x];
            }
            return coms;
        }
    
    
    }
    
    
}