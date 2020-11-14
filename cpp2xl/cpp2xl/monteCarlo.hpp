#pragma once

#include <random>
#include "math.h"
#include "gaussians.hpp"

//Monte-Carlo simulation in the Black-Scholes model
//We simulate the log of stock price

inline double monteCarlo(double spot, double strike, double mat, double rate, double yield, double vol, int nPaths, int nSteps) {
    double dt = mat / nSteps;
    double logS0 = log(spot);
    double logS;
    double result = 0;
    double unif;
    
    double spotAtT;
    double payoff;
    
    std::mt19937 rng(time(0)); //Mersenne Twister, set seed to current time
    
    for (int n=1;n<=nPaths;n++) {
        logS = logS0;
        
        for (int i=1;i<=nSteps;i++) {
            unif = ((double)rng()-(double)rng.min()) / ((double)rng.max()-(double)rng.min()); //generate one random uniform variable
            
            logS = logS + (rate-yield-0.5*vol*vol)*dt+vol*sqrt(dt)*invNormalCdf(unif);
        }
        spotAtT=exp(logS);
        if (spotAtT>strike) {
            payoff = spotAtT - strike;
        } else {
            payoff = 0;
        }
        
        result = result + exp(-rate * mat) * payoff;
    }
    
    return result / nPaths;
}
