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
#include <string>

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
    vector<double> input = {1,0,1,0,1,1,0};
    vector<double> output = {0,1,1,1,0,0,1};
    vector<double> pred;
    vector<double> coef(input.size(),0);
    base_neural_layer<double, double> *one_neural_layer = new neural_layer<double, double, ACT_FUNC::linear>(input.size(), output.size(), INPUT_LAYER_T, 1.0, 0.01);
    std::string cmd;
    int count = 0;

    std::cout<<"==========="<<std::endl;
    std::cout<<*(one_neural_layer)<<std::endl;


    while(true)
    {

        one_neural_layer->activate(input, pred);
        for (double out : pred)
        {
            std::cout<<out<<" ";
        }
        std::cout<<endl;

        for (unsigned idx = 0; idx < pred.size(); ++idx)
        {
            coef.at(idx) = (pred.at(idx) - output.at(idx));
        }

        one_neural_layer->back_propagation(coef);

        ++count;

        if (all_of(coef.begin(), coef.end(), [](double param){ return param < 0.05;}))
        {
            break;
        }
        //if (count % 10 == 0)
        //{
            //std::cin>>cmd;
            //std::cout<<cmd;
            //if (cmd.compare("quit") == 0)
                //break;
        //}
    }
    std::cout<<count<<std::endl;

    delete one_neural_layer;

    //std::cout<<"==========="<<std::endl;
    //std::cout<<one_neural_layer<<std::endl;
    return 0;

}