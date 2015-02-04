/*
 * =====================================================================================
 *
 *       Filename:  neural_layer.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/04/2015 01:50:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef __NEURAL_LAYER_H__
#define __NEURAL_LAYER_H__

#include <vector>
#include <iostream>
#include <algorithm>
//#include <list>

#include "neuron.h"
#include "utils.h"

using std::vector;
using std::ostream;
using std::endl;
using std::for_each;
//using std::list;


template<typename VALUE, typename WEIGHT, typename FUNC>
class neural_layer
{
public:
    neural_layer(int input_size, int output_size, double weight_range=255.):
        input_size_(input_size), output_size_(output_size),
        weight_matrix_(
            vector<vector<WEIGHT> >(output_size_,
                                    vector<WEIGHT>(input_size_)
            )
        )
    {

        for (unsigned idx = 0; idx < output_size_; ++idx)
        {
            neuron_list_.push_back(
                neuron<VALUE, WEIGHT, FUNC>(weight_matrix_.at(idx))
            );
            std::generate_n(weight_matrix_.at(idx).begin(),
                            input_size_,
                            gen_rand(weight_range, idx));
            //std::cout<<neuron_list_.at(idx);
        }
    }

public:
    friend ostream &operator<<(ostream &out, const neural_layer &input)
    {
        for_each(input.neuron_list_.begin(), input.neuron_list_.end(),
                 [&out](const neuron<VALUE, WEIGHT, FUNC> &item)
                        {out<<item<<endl;}
        );
    }

private:
    int input_size_;
    int output_size_;
    vector<neuron<VALUE, WEIGHT, FUNC> > neuron_list_;
    vector<vector<WEIGHT> > weight_matrix_;
};

#endif