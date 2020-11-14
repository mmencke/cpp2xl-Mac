//
//  cpp2xl.hpp
//  cpp2xl
//
//  Created by Magnus Mencke on 14/11/2020.
//  Copyright © 2020 Magnus Mencke. All rights reserved.
//

#pragma once

#include "blackScholes.hpp"
#include "monteCarlo.hpp"
#include "gaussians.hpp"

//extern "C" is needed so the functions have the same name in the dylib as they have here
extern "C" {
    double xNormalDens(double x);
    
    double xNormalCdf(double x);
    
    double xBlackScholes(double spot, double strike, double mat, double rate, double yield, double vol);
    
    double xBS_IV(double spot, double strike, double mat, double rate, double yield, double obsPrice);
    
    double xMonteCarlo(double spot, double strike, double mat, double rate, double yield, double vol, int nPaths, int nSteps);
}
