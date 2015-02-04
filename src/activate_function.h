/*
 * =====================================================================================
 *
 *       Filename:  activate_function.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/04/2015 11:12:57 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef __ACTIVATE_FUNCTION_H__
#define __ACTIVATE_FUNCTION_H__

#include <cassert>
#include <vector>
#include <cmath>

using std::vector;

namespace ACT_FUNC
{

struct linear
{
    template<typename VALUE, typename WEIGHT>
    static VALUE activate(const vector<VALUE> &input, const vector<WEIGHT> &weight)
    {

        assert(input.size() == weight.size());
        VALUE output = 0;

        for (unsigned int idx = 0; idx < input.size(); ++idx)
        {
            output += input.at(idx) * weight.at(idx);
        }

        return output;
    }
};

struct sigmoid
{
    template<typename VALUE, typename WEIGHT>
    static VALUE activate(const vector<VALUE> &input, const vector<WEIGHT> &weight)
    {

        assert(input.size() == weight.size());
        VALUE output = 0;

        for (unsigned int idx = 0; idx < input.size(); ++idx)
        {
            output += input.at(idx) * weight.at(idx);
        }

        return 1./ 1.+ exp(output);
    }
};


};

#endif
