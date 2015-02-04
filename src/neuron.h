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

using std::ostream;
using std::endl;

typedef enum {act_linear, act_sigmoid} activate_function_t;

template<typename T, typename W>
class neuron : public base_neuron<T,W>
{
public:
    neuron(activate_function_t func_type, vector<W> &weight):
        act_func_type_(func_type), weight_vec_(weight)
    {}
public:
    virtual int activate(const vector<T> &input, T &output)
    {
        if (input.size() != weight_vec_.size())
        {
            return -1;
        }

        output = 0;

        for (unsigned int idx = 0; idx < input.size(); ++idx)
        {
            output += input.at(idx) * weight_vec_.at(idx);
        }

        output_ = output;
        return 0;
    }
    virtual const vector<W> &get_weight()
    {
        return weight_vec_;
    }
public:
    friend ostream &operator<<(ostream &out, const neuron<T,W> &input)
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
    activate_function_t act_func_type_;
    vector<W> &weight_vec_;
    T output_;
};

#endif