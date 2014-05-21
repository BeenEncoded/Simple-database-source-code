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


#ifndef VARIABLE_STACK_HPP_INCLUDED
#define VARIABLE_STACK_HPP_INCLUDED
#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace var_stack
{
    
    /** Represents a single variable. */
    template<class type>
    struct variable_data
    {
        std::string name;
        type value;
        
        const variable_data<type>& operator=(const variable_data<type>&);
        bool operator==(const variable_data<type>&) const;
        bool operator!=(const variable_data<type>&) const;
    };
    
    template<class type>
    class stack_class
    {
    public:
        
        /** initializes an empty stack. */
        explicit stack_class() : vars(), var_count(){}
        ~stack_class()
        {
            /* Make sure that vector releases it's memory to us. */
            this->erase_all();
        }
        
        /** Sets one stack equal to another. */
        const stack_class<type>& operator=(const stack_class<type>& s)
        {
            if(this != &s)
            {
                this->erase_all();
                this->var_count = s.var_count;
                this->vars = s.vars;
            }
            return *this;
        }
        
        /** returns a direct reference the Nth index. */
        variable_data<type>& operator[](const unsigned int& x)
        {
            if(x < this->vars.size())
            {
                typename std::map<std::string, variable_data<type> >::iterator tempit(this->vars.begin());
                for(unsigned int loc = 0; ((loc < x) && (tempit != this->vars.end())); loc++)
                {
                    tempit++;
                }
                if(tempit != this->vars.end()) return tempit->second;
            }
            throw "out of bounds!";
            return (this->vars.begin())->second;
        }
        
        /** Returns a constant reference to the Nth index. */
        const variable_data<type>& operator[](const unsigned int& x) const
        {
            if(x < this->vars.size())
            {
                typename std::map<std::string, variable_data<type> >::const_iterator tempit(this->vars.cbegin());
                for(unsigned int loc = 0; ((loc < x) && (tempit != this->vars.cend())); loc++) tempit++;
                if(tempit != this->vars.cend()) return tempit->second;
            }
            throw "out of bounds!";
            return this->vars.cbegin()->second;
        }
        
        /** Returns the number of variables currently stored on the stack. */
        unsigned int size() const
        {
            return this->vars.size();
        }
        
        /** Erases the stack from memory. */
        void erase_all()
        {
            this->vars.erase(this->vars.begin(), this->vars.end());
            this->var_count.erase(this->var_count.begin(), this->var_count.end());
        }
        
        /** Returns a read-only structure of the variable data that matches
        * a variable name.  */
        const variable_data<type>& find_name(const std::string& s)
        {
            typename std::map<std::string, var_stack::variable_data<type> >::iterator element(this->vars.find(s));
            if(element == this->vars.end())
            {
                return (this->vars.begin())->second;
            }
            return element->second;
        }
        
        /** Returns the number of variables that match a specified value. */
        unsigned long long find_values(const type& t) const
        {
            typename std::map<type, unsigned long long>::const_iterator element(this->var_count.find(t));
            if(element == this->var_count.end()) return 0;
            return element->second;
        }
        
        /** Returns true if the variable in question does exist. */
        bool var_exists(const std::string& s) const
        {
            return (this->vars.find(s) != this->vars.end());
        }
        
        /** adds the variable to the stack if it does not exist.
        * Changes a variable's value if it does exist. */
        void set_var(const std::string& name, const type& val)
        {
            type temp_val(this->vars[name].value);

            /* Remove this variable from the count before over-writing it.*/
            if(this->var_exists(name))
            {
                this->var_count[temp_val]--;

                //if there are not more vars equal to the value, erase it from the count
                if(this->var_count[temp_val] == 0)
                {
                    this->var_count.erase(temp_val);
                }
            }

            //over-write the old variable
            this->vars[name].name = name;
            this->vars[name].value = val;

            //update the count
            switch(this->var_count.find(val) == this->var_count.end())
            {
                case true:
                {
                    this->var_count[val] = 1;
                }
                break;

                case false:
                {
                    this->var_count[val]++;
                }
                break;

                default:
                {
                }
                break;
            }
        }
        
        /** Removes a variable from the stack, if it exists.  Also decreases value
        * count of the variable's value. */
        void remove_var(const std::string& name)
        {
            if(this->vars.find(name) != this->vars.end())
            {
                type temp_val(this->vars[name].value);
                this->var_count[temp_val]--;
                if(this->var_count[temp_val] == 0)
                {
                    this->var_count.erase(temp_val);
                }

                this->vars.erase(name);
            }
        }
        
        
    private:
        std::map<std::string, variable_data<type> > vars;
        std::map<type, unsigned long long> var_count;
        
        
    };
    
    template class stack_class<int>;
//    template class stack_class<unsigned int>;
//    template class stack_class<std::string>;
//    template class stack_class<unsigned long long>;
//    template class stack_class<unsigned long>;
//    template class stack_class<long>;
//    template class stack_class<float>;
//    template class stack_class<double>;
//    template class stack_class<long double>;
}

#endif