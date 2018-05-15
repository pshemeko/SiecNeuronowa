//
// Created by Przemo on 2018-05-15.
//

#include "../headers/Neuron.h"

Neuron::Neuron(int iloscWejsc, bool bias) // nie potrzebuje tego biasu na wejsciu tutaj bo zawsze vektor wag o jedne wiekrzy i przy liczeniu sumy
  : czyJestBias{bias} , wartoscBiasu{1.0} , blad{0.0} ,wyjscie{0.0}
{
    Losowanie los(-0.5, 0.5);
    for(int i = 0; i < iloscWejsc + 1; ++i) // tworze o jedna wage wiecej na bias // moge to zmienic zeby 1 wiekrzy tylko gdy bias
    {
        wagi.push_back(los.losujWagi() );
        stareWagi.push_back(0.0);
    }




}