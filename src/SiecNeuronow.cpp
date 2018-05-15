//
// Created by Przemo on 2018-05-16.
//

#include "../headers/SiecNeuronow.h"

SiecNeuronow::SiecNeuronow(vector<int> iloscNeuronowNaWarstweDomyslna ) // ilosc neuronow na arstwe to wektor ktory zawiera na kazdej pozycji ile neuronow jest w danej warstwie
        : iloscNeuronowNaWarstwe{iloscNeuronowNaWarstweDomyslna}
{
    // tworze warstwe rozprowadzajaca

    vector<Neuron*> rozprowadzajaca ;
    for (int i = 0; i < iloscNeuronowNaWarstwe[0]; ++i )
    {
        rozprowadzajaca.push_back( new Neuron(1,CZY_BIAS));
        rozprowadzajaca[i]-> wagi[0]=1.0;   // bo warstwa wejsciowa jest tylko do rozprowadzenia sygnalu wiec tam wag nie ma
        rozprowadzajaca[i]-> wagi[1]=0.0;   //TODO sprawdzic ale chyba w rozprowadzajacej nie ma biasu wiec jego wage zeruje
    }
    siecNeuronow.push_back(rozprowadzajaca);   // dla warstwy wejsciowej

    // tworze siec

    for(int j = 1; j < iloscNeuronowNaWarstwe.size(); ++j) //tworze warstwy ukryte i wyjsciowa
    {
        vector<Neuron*> warstwa ;

        for (int i = 0; i < iloscNeuronowNaWarstwe[j];++i)
        {
            warstwa.push_back(new Neuron(iloscNeuronowNaWarstwe[j-1],CZY_BIAS));
        }
        siecNeuronow.push_back(warstwa);
    }
}

double SiecNeuronow::bladSieci()
{
    int ostWarstwa = iloscNeuronowNaWarstwe.size() - 1;
    double suma = 0.0;

    for(int i = 0; i < iloscNeuronowNaWarstwe[ostWarstwa]; ++i)
    {
        double ile = siecNeuronow[ostWarstwa-1][i] -> blad;
        suma += 0.5*ile*ile;
    }
    return suma/(double)iloscNeuronowNaWarstwe[ostWarstwa];
}