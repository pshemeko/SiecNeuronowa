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

/*
static double funkcjaAktywacji(double x, double beta = 1.0)
{
    //double beta = 1.0; // wspczynnik
    return 1.0 / ( 1.0 + exp(-beta * x));
}
 */
/*
static double pochodnaFunkcjiAktywacji(double x, double beta = 1.0)
{
    //double beta = 1.0;
    return beta * funkcjaAktywacji(x, beta) * (1.0 - funkcjaAktywacji(x, beta));
}
*/

//informacja ze sprawka mlodego
//Istotną zaletą logistycznej funkcji aktywacji jest łatwość obliczania jej pochodnej,
// //jeżeli w pamięci przechowuje się jedynie jej wartość (nawet nie dysponując argumentem dla którego
// została ona obliczona) - okazuje się, że:
//   pochodna(x) = funkcja(x) · (1 − funkcja(x))
/*
static double pochodnaFunkcjiAktywacji(double x, double beta = 1.0)
{
    return  beta * x * (1 -  x);
}
*/


#endif //KWIATKI_MATEMATYKA_H
