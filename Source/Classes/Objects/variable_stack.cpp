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

#include "variable_stack.hpp"

namespace
{
}

namespace var_stack
{
    /** Sets the value of a variable equal to the value of another.
     does not copy the name!!*/
    template<class type>
    const variable_data<type>& variable_data<type>::operator=(const variable_data<type>& var)
    {
        if(this != &var)
        {
            this->value = var.value;
        }
        return *this;
    }
    
    /** Returns true if the value of a variable is equal to the value
     of another variable.*/
    template<class type>
    bool variable_data<type>::operator==(const variable_data<type>& var) const
    {
        return (this->value == var.value);
    }
    
    /** Returns true if the value of another vairable is not equal to
     this variable. */
    template<class type>
    bool variable_data<type>::operator!=(const variable_data<type>& var) const
    {
        return !(this->operator==(var));
    }
    
    
}