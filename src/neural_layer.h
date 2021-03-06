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

#include "base_neural_layer.h"
#include "neuron.h"
#include "utils.h"

using std::vector;
using std::ostream;
using std::endl;
using std::for_each;
//using std::list;

typedef enum {
    OUTPUT_LAYER_T,
    HIDDEN_LAYER_T
} neural_layer_t;

typedef enum {
    BINARY_LINEAR_T,
    LINEAR_T,
    SIGMOID_T
} activate_method_t;

template<typename VALUE, typename WEIGHT, typename FUNC>
class neural_layer: public base_neural_layer<VALUE, WEIGHT>
{
public:
    neural_layer(int input_size, int output_size,
                 neural_layer_t layer_type = OUTPUT_LAYER_T,
                 double weight_range=1.,
                 double learning_rate = 0.01,
                 VALUE threshold = 0):
        input_size_(input_size), output_size_(output_size),
        weight_matrix_(
            vector<vector<WEIGHT> >(output_size_,
                                    vector<WEIGHT>(input_size_, learning_rate)
            )
        ),
        layer_type_(layer_type),
        weight_range_(weight_range),
        learning_rate_(learning_rate),
        threshold_(threshold)

    {

        for (unsigned idx = 0; idx < output_size_; ++idx)
        {
            neuron_list_.emplace_back(
                neuron<VALUE, WEIGHT, FUNC>(weight_matrix_.at(idx),
                                            learning_rate_,
                                            threshold_)
            );
            std::generate_n(weight_matrix_.at(idx).begin(),
                            input_size_,
                            gen_rand(weight_range, idx));
            //std::cout<<neuron_list_.at(idx);
        }
    }
public:
    virtual int activate(const vector<VALUE> &input, vector<VALUE> &output)
    {
        output.clear();
        for (auto &neuron : neuron_list_)
        {
            VALUE one_output;
            neuron.activate(input, one_output);
            output.push_back(one_output);
        }
        return 0;
    }

    virtual int back_propagation(const vector<VALUE> grad_coef)
    {
        assert(grad_coef.size() == neuron_list_.size());

        for (unsigned int idx = 0; idx < neuron_list_.size(); ++idx)
        {
            neuron_list_.at(idx).back_propagation(grad_coef.at(idx));
        }

        return 0;
    }
    virtual vector<VALUE> get_delta(const vector<VALUE> next_layer_delta)
    {
        vector<VALUE> delta(input_size_, 0);

        for (unsigned int input_idx = 0;
             input_idx < input_size_;
             ++input_idx)
        {
            for (unsigned int output_idx = 0;
                 output_idx < output_size_;
                 ++output_idx)
            {
                WEIGHT tmp_delta = next_layer_delta.at(output_idx);

                delta.at(input_idx) +=
                    weight_matrix_.at(output_idx).at(input_idx) *
                    neuron_list_
                        .at(output_idx)
                        .get_delta(next_layer_delta.at(output_idx));
            }
        }

        return delta;
    }

public:
    //friend ostream &operator<<(ostream &out, const neural_layer<VALUE, WEIGHT, FUNC> &input)
    virtual void printTo(ostream &out) const
    {
        for_each(neuron_list_.begin(), neuron_list_.end(),
                 [&out](const neuron<VALUE, WEIGHT, FUNC> &item)
                        {out<<item<<endl;}
        );
    }

private:
    int input_size_;
    int output_size_;
    vector<neuron<VALUE, WEIGHT, FUNC> > neuron_list_;
    vector<vector<WEIGHT> > weight_matrix_;

    neural_layer_t layer_type_;
    double weight_range_;
    double learning_rate_;
    VALUE threshold_;
};

#endif