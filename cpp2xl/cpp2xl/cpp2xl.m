//
//  cpp2xl.m
//  cpp2xl
//
//  Created by Magnus Mencke on 11/03/2020.
//  Copyright © 2020 Magnus Mencke. All rights reserved.
//

#import "cpp2xl.h"
#import "blackScholes.h"
#include "monteCarlo.h"
#import "gaussians.h"


@implementation cpp2xl

double xNormalDens(double x){
    return normalDens(x);
}

double xNormalCdf(double x){
    return normalCdf(x);
}

double xMultiply2Numbers(double a, double b){
    return a * b;
}

double xBlackScholes(double spot, double strike, double mat, double rate, double vol) {
    return blackScholes(spot, strike, mat, rate, vol);
}
double xBlackScholes2(double spot, double strike, double mat, double rate, double vol) {
    return blackScholes(spot, strike, mat, rate, vol);
}


double xBS_IV(double spot, double strike, double mat, double rate, double obsPrice) {
    double ub=2;
    double lb=0.0001;
    double mb;
    double bs;
    
    do {
        mb=0.5*(ub+lb);
        
        bs=blackScholes(spot, strike, mat, rate, mb);
        
        if (bs>obsPrice) {
            ub=mb;
        } else {
            lb=mb;
        }
        
    } while(ub-lb>0.0001);
    return 0.5*(ub+lb);
}
double xMonteCarlo(double spot, double strike, double mat, double rate, double vol, int nPaths, int nSteps) {
    return monteCarlo(spot, strike, mat, rate, vol, nPaths, nSteps);
}

@end
