/*
 * =====================================================================================
 *
 *       Filename:  neuron.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/03/2015 06:14:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef __NEURON_H__
#define __NEURON_H__

#include <cassert>
#include <iostream>

#include "base_neuron.h"
#include "activate_function.h"

using std::ostream;
using std::endl;


template<typename VALUE, typename WEIGHT, typename FUNC>
class neuron : public base_neuron<VALUE,WEIGHT>
{
private:
    typedef VALUE (*activate_function_t)(const vector<VALUE>&, const vector<WEIGHT>&);


public:
    neuron(vector<WEIGHT> &weight):
        weight_vec_(weight),
        activate_func(FUNC::template activate<VALUE, WEIGHT>),
        output_(0)
    {}
    neuron(const neuron<VALUE, WEIGHT, FUNC> &other):
        weight_vec_(other.weight_vec_),
        activate_func(other.activate_func),
        output_(other.output_)
    {}
public:
    virtual int activate(const vector<VALUE> &input, VALUE &output)
    {
        if (input.size() != weight_vec_.size())
        {
            return -1;
        }

        //output_ = FUNC::template activate<VALUE,WEIGHT>(input, weight_vec_);
        output_ = activate_func(input, weight_vec_);
        return 0;
    }
    virtual const vector<WEIGHT> &get_weight()
    {
        return weight_vec_;
    }
public:
    friend ostream &operator<<(ostream &out, const neuron<VALUE,WEIGHT,FUNC> &input)
    {
        out<<"Weights: ";

        for (auto a_weight : input.weight_vec_)
        {
            out<<a_weight<<" ";
        }
        out<<endl;

        out<<"Output: ";
        out<<input.output_;
        out<<endl;
    }


private:
    vector<WEIGHT> &weight_vec_;
    activate_function_t activate_func;
    VALUE output_;
};

#endif