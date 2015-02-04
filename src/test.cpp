/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/03/2015 06:20:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>

#include "neuron.h"

int main()
{
    vector<vector<double> > weight;
    weight.push_back(vector<double>());

    double output;
    vector<double> input = {1,0,0,0};

    weight.at(0).push_back(1);
    weight.at(0).push_back(2);
    weight.at(0).push_back(3);
    weight.at(0).push_back(4);

    neuron<double, double> one_neuron(act_linear, weight.at(0));

    one_neuron.activate(input, output);

    std::cout<<one_neuron<<std::endl;

    return 0;

}