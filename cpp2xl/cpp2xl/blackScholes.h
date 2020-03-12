#include "math.h"
#include "gaussians.h"

double blackScholes(double spot, double strike, double mat, double rate, double vol) {
double std = sqrt(mat) * vol;

double halfVar = 0.5 * std * std;

double d1 = (log(spot / strike) + rate * mat + halfVar) / std;

double d2 = d1 - std; 

return spot * normalCdf(d1) - exp(-rate * mat) * strike * normalCdf(d2);
}