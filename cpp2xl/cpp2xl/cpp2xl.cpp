#include "cpp2xl.hpp"

double xNormalDens(double x){
    return normalDens(x);
}

double xNormalCdf(double x){
    return normalCdf(x);
}

double xBlackScholes(double spot, double strike, double mat, double rate, double yield, double vol) {
    return blackScholes(spot, strike, mat, rate, yield, vol);
}

//Simple algorithm to find implied volatility
double xBS_IV(double spot, double strike, double mat, double rate, double yield, double obsPrice) {
    double ub=2;
    double lb=0.0001;
    double mb;
    double bs;
    
    do {
        mb=0.5*(ub+lb);
        
        bs=blackScholes(spot, strike, mat, rate,yield, mb);
        
        if (bs>obsPrice) {
            ub=mb;
        } else {
            lb=mb;
        }
        
    } while(ub-lb>0.0001);
    return 0.5*(ub+lb);
}

double xMonteCarlo(double spot, double strike, double mat, double rate, double yield, double vol, int nPaths, int nSteps) {
    return monteCarlo(spot, strike, mat, rate, yield, vol, nPaths, nSteps);
}
