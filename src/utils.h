/*
 * =====================================================================================
 *
 *       Filename:  utils.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/04/2015 02:50:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <random>
#include <ctime>

struct gen_rand
{
    double range;
public:
    gen_rand(double r=1.0, double seed=5.0): range(r)
    {
        srand(time(NULL)+seed);
    }

    double operator()()
    {
        return (rand()/(double)RAND_MAX) * range;
    }
};
#endif
