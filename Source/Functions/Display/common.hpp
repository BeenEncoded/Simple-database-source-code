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
 * 
 * I recognize that most of these functions are common in all programs, so...  I
 * wouldn't care if you used them.
 */

#ifndef COMMON_HPP_INCLUDED
#define COMMON_HPP_INCLUDED
#include <iostream>
#include <string>

namespace common
{
    
    /** Removes the excess characters from the input buffer. */
    inline void cl()
    {
        using std::cin;
        while(cin.rdbuf()->in_avail() > 0) cin.get();
    }
    
    /** Clears the screen by displaying 200 newline characters. */
    inline void cls()
    {
        using std::cout;
        for(int x = 0; x < 200; x++) cout<< '\n';
        cout.flush();
        cout.clear();
    }
    
    /** Retrieves 1 character, and keeps the buffer cleared. This
     is BUFFERED input, but only the first character is returned, and
     the rest is discarded.*/
    inline char getch()
    {
        using std::cin;
        char ch(0);
        cl();
        cin.get(ch);
        cl();
        return ch;
    }
    
    void center(const std::string&);
    
    bool is_letter(const char&);
    bool is_number(const char&);
    bool is_special(const char&);
    bool is_char(const char&);
    
    bool string_is_int(const std::string&);
    
    
}

#endif