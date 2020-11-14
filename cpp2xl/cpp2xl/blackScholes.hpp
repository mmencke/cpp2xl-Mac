#pragma once

#include "math.h"
#include "gaussians.hpp"

// http://www.nematrian.com/BlackScholesGreeksVanillaCalls
// Black-Scholes formula with continuous dividend yield

inline double d1Func(double spot, double strike, double mat, double rate, double yield, double vol) {
    
    double std = sqrt(mat) * vol;
    
    return (log(spot / strike) + rate * mat - yield * mat + 0.5 * std * std) / std;
}

inline double blackScholes(double spot, double strike, double mat, double rate, double yield, double vol) {
    double std = sqrt(mat) * vol;

    double d1 = d1Func(spot,strike,mat,rate,yield,vol);

    double d2 = d1 - std;

    return exp(-yield * mat) * spot * normalCdf(d1) - exp(-rate * mat) * strike * normalCdf(d2);
}