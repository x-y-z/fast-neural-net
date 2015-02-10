/*
 * =====================================================================================
 *
 *       Filename:  neural_net.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/09/2015 11:07:16 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef __NEURAL_NET__
#define __NEURAL_NET__

#include <vector>
#include <memory>


#include "base_neural_layer.h"
#include "neural_layer.h"
#include "activate_function.h"


using std::vector;
using std::unique_ptr;

template<typename VALUE, typename WEIGHT>
class neural_net
{
public:
    neural_net(const vector<int> &layer_info,
               const vector<activate_method_t> &layer_act_method,
               double weight_range=1.,
               double learning_rate = 0.01,
               VALUE threshold = 0):
        weight_range_(weight_range),
        learning_rate_(learning_rate),
        threshold_(threshold)
    {
        assert(layer_info.size() == layer_act_method.size() + 1);
        //at least one input layer, one output layer
        assert(layer_info.size() > 1);

        vector<neural_layer_t> layer_type(layer_info.size(), HIDDEN_LAYER_T);
        layer_type.back() = OUTPUT_LAYER_T;

        for (unsigned idx = 0; idx < layer_info.size() - 1; ++idx)
        {
            switch (layer_act_method.at(idx))
            {
                default:
                case LINEAR_T:
                    {
                        all_layers_.emplace_back(
                            new neural_layer<VALUE, WEIGHT, ACT_FUNC::linear>(
                                        layer_info.at(idx),
                                        layer_info.at(idx+1),
                                        layer_type.at(idx),
                                        weight_range,
                                        learning_rate,
                                        threshold
                                )
                            );
                    }
                    break;
                case BINARY_LINEAR_T:
                    {
                        all_layers_.emplace_back(
                            new neural_layer<VALUE, WEIGHT,
                                             ACT_FUNC::binary_linear>(
                                        layer_info.at(idx),
                                        layer_info.at(idx+1),
                                        layer_type.at(idx),
                                        weight_range,
                                        learning_rate,
                                        threshold
                                )
                            );
                    }
                    break;
                case SIGMOID_T:
                    {
                        all_layers_.emplace_back(
                            new neural_layer<VALUE, WEIGHT, ACT_FUNC::sigmoid>(
                                        layer_info.at(idx),
                                        layer_info.at(idx+1),
                                        layer_type.at(idx),
                                        weight_range,
                                        learning_rate,
                                        threshold
                                )
                            );
                    }
                    break;
            }
        }

    }
public:
    virtual int train(const vector<VALUE> &input,
                      const vector<VALUE> &expected_output,
                      unsigned int times = 1)
    {
        vector<VALUE> dummy;
        for (unsigned int iteration = 0; iteration < times; ++iteration)
        {
            activate(input, dummy);
            back_propagation(expected_output);
        }

        return 0;
    }
    virtual int predict(const vector<VALUE> &input, vector<VALUE> &output)
    {
        return activate(input, output);
    }
private:
    virtual int activate(const vector<VALUE> &input,
                         vector<VALUE> &output)
    {
        vector<VALUE> intermediate_input(input);
        vector<VALUE> intermediate_output;
        for (auto &one_layer : all_layers_)
        {
            one_layer->activate(intermediate_input, intermediate_output);

            intermediate_input = intermediate_output;
        }

        prev_output_ = output = intermediate_output;

        return 0;
    }
    virtual int back_propagation(const vector<VALUE> &expected_output)
    {
        assert(expected_output.size() == prev_output_.size());

        vector<VALUE> coef(expected_output.size(), 0);

        for (unsigned int idx = 0; idx < expected_output.size(); ++idx)
        {
            coef.at(idx) = prev_output_.at(idx) - expected_output.at(idx);
        }

        for (auto one_layer = all_layers_.rbegin();
             one_layer < all_layers_.rend();
             ++one_layer)
        {
            (*one_layer)->back_propagation(coef);

            coef = (*one_layer)->get_delta(coef);
        }

        return 0;
    }

private:
    vector<unique_ptr<base_neural_layer<VALUE,WEIGHT> > > all_layers_;

    vector<VALUE> prev_output_;
    double weight_range_;
    double learning_rate_;
    VALUE threshold_;
};

#endif