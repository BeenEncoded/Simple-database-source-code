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

#include <iostream>
#include <string>

#include "global_defines.hpp"

namespace
{
}

namespace common
{
    /** Returns true if ch represents a number. */
    bool is_number(const char& ch)
    {
        return (std::string(NUMBERS).find_first_of(ch) != std::string::npos);
    }
    
    /** Returns true if ch represents a letter. */
    bool is_letter(const char& ch)
    {
        return (std::string(LETTERS).find_first_of(ch) != std::string::npos);
    }
    
    /** Returns true if ch represents a special character. */
    bool is_special(const char& ch)
    {
        return (std::string(SPECIALS).find_first_of(ch) != std::string::npos);
    }
    
    /** Returns true if ch represents a character that can be printed. */
    bool is_char(const char& ch)
    {
        return (is_number(ch) || is_letter(ch) || is_special(ch));
    }
    
    /** Returns true if s represents an integer. */
    bool string_is_int(const std::string& s)
    {
        for(char c : s) if(!is_number(c)) return false;
        return true;
    }
    
    /** Displays a string in the horizontal center.  
     * (40 - (string.size() / 2)) spaces.  */
    void center(const std::string& s)
    {
        using std::cout;
        
        unsigned int cent((s.size() / 2));
        switch((unsigned int)HCENTER >= cent)
        {
            case true:
            {
                cent = ((unsigned int)HCENTER - cent);
            }
            break;
            
            case false:
            {
                cent = 0;
            }
            break;
            
            default:
            {
            }
            break;
        }
        for(unsigned int x = 0; x < cent; x++) cout<< ' ';
        cout<< s;
    }
    
    
}