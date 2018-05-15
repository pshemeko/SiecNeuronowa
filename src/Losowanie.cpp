/*
 * File:   Losowanie.cpp
 * Author: Przemo
 *
 * Created on 15 kwietnia 2018, 10:16
 */

#include "../headers/Losowanie.h"


Losowanie::Losowanie(double dolnyZakres, double gornyZakres)
        : dist{dolnyZakres, gornyZakres}, liczbaNaturalna{(int)dolnyZakres, (int)gornyZakres},
          min{dolnyZakres}, max{gornyZakres}
{
    rng.seed(random_device()());
}

double Losowanie::losujWagi()
{
    return dist(rng);
}
/*
Losowanie& Losowanie::get()
{
    static Losowanie instance(min,max);
    return instance;
}
*/
Losowanie::~Losowanie()
{
    //dtor
}

int Losowanie::losujInt()
{
    return liczbaNaturalna(rng);
}
