/*
 * =====================================================================================
 *
 *       Filename:  base_neuron.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/03/2015 06:06:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef __BASE_NEURON_H__
#define __BASE_NEURON_H__

#include <vector>

using std::vector;

/*
 * weight vector has to be constructed before get any neurons.
 */
template<typename VALUE, typename WEIGHT>
class base_neuron
{
public:
    virtual int activate(const vector<VALUE> &input, VALUE &output) = 0;
    virtual const vector<WEIGHT> & get_weight() = 0;
    virtual int back_propagation(const VALUE &actual_output) = 0;
};

#endif //__BASE_NEURON_H__