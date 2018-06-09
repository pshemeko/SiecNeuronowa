//
// Created by pobi on 5/14/18.
//

#ifndef KWIATKI_MATEMATYKA_H
#define KWIATKI_MATEMATYKA_H

#include <math.h>

static double funkcjaSasiedztwaGazuNeuronowego(int ktoreSasiedztwo, double lambda)
{
//if(lambda < 0.0000001) lambda = 0.0000001;

return pow(M_E, -(double)ktoreSasiedztwo/lambda);
}



#endif //KWIATKI_MATEMATYKA_H
