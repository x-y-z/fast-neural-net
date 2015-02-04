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

#include "activate_function.h"
#include "neural_layer.h"

int main()
{
    //vector<vector<double> > weight;
    //weight.push_back(vector<double>());

    //double output;
    //vector<double> input = {1,0,0,0};

    //weight.at(0).push_back(1);
    //weight.at(0).push_back(2);
    //weight.at(0).push_back(3);
    //weight.at(0).push_back(4);

    //neuron<double, double, ACT_FUNC::linear> one_neuron(weight.at(0));

    //one_neuron.activate(input, output);

    //std::cout<<one_neuron<<std::endl;
    neural_layer<unsigned short, unsigned short, ACT_FUNC::linear> one_neural_layer(4, 5);

    //std::cout<<"==========="<<std::endl;
    std::cout<<one_neural_layer<<std::endl;
    return 0;

}