//
// Created by Przemo on 2018-05-15.
//

#include "../headers/Neuron.h"

Neuron::Neuron(vector<int> zakres)
{
    for(int i = 0; i <  zakres.size() / 2 ; i++)
    {
        Losowanie los(zakres[i * 2], zakres[ i * 2 + 1]);
        wagi.push_back(los.losujWagi() );
    }
}

Neuron::Neuron( double x, double y)
{
    wagi.push_back(x);
    wagi.push_back(y);
}