#include "math.h"
#include "gaussians.h"
#include "stdlib.h"

double monteCarlo(double spot, double strike, double mat, double rate, double vol, int nPaths, int nSteps) {
    double dt = mat / nSteps;
    double logS0 = log(spot);
    double logS;
    double result = 0;
    double rnd;
    
    double spotAtT;
    double payoff;
    
    for (int n=1;n<=nPaths;n++) {
        logS = logS0;
        
        for (int i=1;i<=nSteps;i++) {
            rnd = ((double)rand() / (double)(RAND_MAX));
            
            logS = logS + (rate-0.5*vol*vol)*dt+vol*sqrt(dt)*invNormalCdf(rnd);
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
