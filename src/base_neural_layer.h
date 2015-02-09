/*
 * =====================================================================================
 *
 *       Filename:  base_neural_layer.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/09/2015 01:08:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef __BASE_NEURAL_LAYER__
#define __BASE_NEURAL_LAYER__

#include <iostream>

using std::ostream;


template<typename VALUE, typename WEIGHT>
class base_neural_layer
{
public:
    virtual int activate(const vector<VALUE> &input, vector<VALUE> &output) = 0;
    virtual int back_propagation(const vector<VALUE> grad_coef) = 0;
public:
    virtual void printTo(ostream &out) const = 0;
public:
    friend ostream &operator<<(ostream &out, const base_neural_layer<VALUE, WEIGHT> &output)
    {
        output.printTo(out);
        return out;
    }
};


#endif