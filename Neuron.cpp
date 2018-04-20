/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Neuron.cpp
 * Author: Przemo
 *
 * Created on 15 kwietnia 2018, 10:14
 */
#include "Neuron.h"
#include "Losowanie.h"

Neuron::Neuron(int iloscWejsc, bool bias) // nie potrzebuje tego biasu na wejsciu tutaj bo zawsze torze vektor o jedne wiekrzy i przy liczeniu sumy
                                           // mnoze ostatni element razy bIAS ( czyli 1 ub 0)
{
    //if(bias) wagi.push_back(Losowanie::get().losuj());

    for(int i = 0; i < iloscWejsc + 1; ++i) // tworze o jedna wage wiecej na bias
    {
        wagi.push_back(Losowanie::get().losuj());
        stareWagi.push_back(0.0);
        //wejsciaNeuronu.push_back(0.0);
    }
       // bias jest na koncu dodawany
    czyJestBias = bias;
    wartoscBiasu = 1.0;
    blad = 0.0;
}
//??????
void Neuron::obliczWyjscieSumatora(Wektor wejscie) // popraw bo bias jest 0
{
    float suma = 0.0;
    for(unsigned int i = 0; i < wejscie.size(); ++i)
    {
        suma += wejscie[i] * wagi[i];
    }
    if(czyJestBias) suma +=wagi[wagi.size()-1] * wartoscBiasu;
    wyjscieSumatora = suma;
    //wyjscie = funkcjaAktywacji(suma);
}
double Neuron::funkcjaAktywacji(double x)
{
return 1.0/(1.0 + pow(M_PI, -x) );
}

double Neuron::pochodnaFunkcjiAktywacji(double x)
{
    double wartosc = funkcjaAktywacji(x);
    return wartosc*(1.0 - wartosc);

   // return funkcjaAktywacji(x) * (1.0 - funkcjaAktywacji(x) );
}

void Neuron::setWyjscie(double x)
{
    wyjscieSumatora = x;
    wyjscie = funkcjaAktywacji(x);
}


Neuron::~Neuron()
{
    //dtor
}

void Neuron::przepiszDoStarejWagi()
{
    for(int i = 0; i< wagi.size(); ++i)
    {
        stareWagi[i] = wagi[i];
    }
}

string Neuron::wypisz()
{
    ostringstream os;
    os << " Blad: " << blad << "\tWyjscie:" <<wyjscie << "\twyjscieSumator:" <<wyjscieSumatora << "\tWagi:";
    for(int i = 0; i< wagi.size(); i++) os << wagi[i] << " ";
    os << "\tStare wagi:";
    for(int i = 0; i< stareWagi.size(); i++) os << stareWagi[i] << " ";
    return os.str();

}