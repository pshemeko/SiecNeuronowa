/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SiecNeuronow.cpp
 * Author: Przemo
 * 
 * Created on 15 kwietnia 2018, 10:18
 */

#include "SiecNeuronow.h"

// tylko dodalem
//musze testowac gita

SiecNeuronow::SiecNeuronow(int iloscWarstw,vector<int> iloscNeuronowNaWarstwe2)//, int neuronowNaKazdejWarstwieUkrytej)
    : iloscNeuronowNaWarstwe{iloscNeuronowNaWarstwe2}
{
    // po to by ainicoweac wejscia i wyjscia
    
    temp();
    
    // tworze wektor wejscie
    vector<double> doWyliczenWyjsc;
    for (int i = 0; i < iloscNeuronowNaWarstwe[0]; ++i ) // tworze wesciawa warstwe
    {
        //Neuron nowyNeuron = Neuron(1,CZY_BIAS);
        wejscie.push_back( new Neuron(1,CZY_BIAS));
        doWyliczenWyjsc.push_back(1.0);
    }
    siecWyjsc.push_back(doWyliczenWyjsc);   // dla warstwy wejsciowej
    // tworze siec
    // ilosc neuronow na arstwe to wektor ktory zawiera na kazdej pozycji ile neuronow jest w danej warstwie
    // na poz 0 jest ile jest na warstwie ukrytej dlatego tutaj jest od 1
    for(int j = 1; j < iloscNeuronowNaWarstwe.size(); ++j) //tworze warstwy ukryte i wyjsciowa
    {    
        vector<Neuron*> warstwa ;
        vector<double> wynikiTMP;

        for (int i = 0; i < iloscNeuronowNaWarstwe[j];++i)
        {
            
            if(j = 1) {  // jesli jest to warstwa 1 czyli pierwsza za wejsciowa to musi pobierac dane z warstwy wejsciowej
                        //Neuron neuronik =  Neuron(ILOSCWEJSC,CZY_BIAS);
                        warstwa.push_back(new Neuron(ILOSCWEJSC,CZY_BIAS));
                        }
            else {
                //Neuron neuronik =  Neuron(iloscNeuronowNaWarstwe[j-1],CZY_BIAS);
                warstwa.push_back(new Neuron(iloscNeuronowNaWarstwe[j-1],CZY_BIAS));
            }
            wynikiTMP.push_back(1.0);
            
        }
        siecNeuronow.push_back(warstwa);
        siecWyjsc.push_back(wynikiTMP);
    }
}

SiecNeuronow::~SiecNeuronow()
{
    //dtor
}

// obliczamy wyjscia kazdego neuronu
void SiecNeuronow::obliczanieWag(vector<int> danaWej) // SPRAWDZAC CZY ILOSC ELEMENTOW daneWej JEST TAKA JAK WIELKOSC WARSTWY POCZATKOWEJ
{
    //losowanie danej wejsciowej
    //vector<int> danaWej = daneWejsciowe[0];
    //vector<double> doWejscia;
    //doWejscia.push_back(1.0);
    // podawanie danych na warstwe wejsciowa
    for(unsigned int i = 0; i < iloscNeuronowNaWarstwe[0]; ++i)
    {
        double wartosc = danaWej[i] * wejscie[i]->wagi[0] + CZY_BIAS * wejscie[i]->wagi[1]; // bias jest ostatnim elem w wektorze
        wejscie[i]->setWyjscie(wartosc); 
        siecWyjsc[0][i] = wejscie[i]->wyjscie;
    }
    
    //vector<double> wyjsciaWarstwy;
/*    for(int i = 0; i < iloscNeuronowNaWarstwe[0]; i++)  // tworze wwektor wyjsc wartwy 0
    {
        //wyjsciaWarstwy.push_back(wejscie[i]->wyjscie);  
        siecWyjsc[0][i] = wejscie[i]->wyjscie; // dodaje do pirwszej pozycje wzystkie wyjscia wyliczone z warstwy wejsciowej
    }
 */
    //siecWyjsc.push_back(wyjsciaWarstwy);
    
    
    //podawanie danych na dalsze warstwy    
    // to jest funkcja liczenie wag wyjeta z neuronu i teraz jest liczona tutaj  // mozna ja skasowac z neuronu
    for(int i = 1; i < iloscNeuronowNaWarstwe.size(); ++i)// lece pokolei po warstwach
            // chyba od i=0 ????? bo jest wejscie a to sa neurony w warstwie ukrytej i do size()-1
        //TODO ZMIENIC CHYBA!!!!!!!!!!!!!!!
    {
        for(int j = 0; j < iloscNeuronowNaWarstwe[i]; ++j) // dla kazdego neuronu w tej warstwie licze jego wyjscie
        {
            double suma = 0.0;
            for(int k = 0; k < iloscNeuronowNaWarstwe[i-1]; ++k)
            {
                suma += siecWyjsc[i-1][k] * (siecNeuronow[i][j]->wagi[k] );
            }
            suma += CZY_BIAS * siecNeuronow[i][j]->wagi[iloscNeuronowNaWarstwe[i-1]];   // gdy bias to trzeba go jeszcze dodac i przemnozyc przez jego wagee
                                                                // waga biasu jest ostatnia w wektorze wag zawze jest o jedna waga wiecej w neuonie gdyby bias byl
            siecNeuronow[i][j]->setWyjscie(suma);
            siecWyjsc[i][j] = siecNeuronow[i][j]->wyjscie;   
        }
    }
}

void SiecNeuronow::temp()   // inicjuje dane wejsciowe
{
    vector<int> wek  = {1,0,0,0};
    vector<int> wek1 = {0,1,0,0};
    vector<int> wek2 = {0,0,1,0};
    vector<int> wek3 = {0,0,0,1};
//wek.push_back(1);
daneWejsciowe.push_back(wek);
daneWyjsciowe.push_back(wek);
daneWejsciowe.push_back(wek1);
daneWyjsciowe.push_back(wek1);
daneWejsciowe.push_back(wek2);
daneWyjsciowe.push_back(wek2);
daneWejsciowe.push_back(wek3);
daneWyjsciowe.push_back(wek3);


}


void SiecNeuronow::obliczanieBledow(vector<int> danaWyj)
{
    int ostWarstwa = iloscNeuronowNaWarstwe.size() - 1;
    //dla kazdego neuronu w warstwie wyjsciowej obliczam jego blad a potem poopaguje te bledy wtecz
    for(int i = 0; i < iloscNeuronowNaWarstwe[ostWarstwa]; ++i)
    {
        siecNeuronow[ostWarstwa][i] -> blad = (siecNeuronow[ostWarstwa][i] -> wyjscie) - danaWyj[i];    
    }
    // teraz trzeba propagowac wstecz
    
    for (int i = iloscNeuronowNaWarstwe.size() - 2; i >= 0; --i) // dla 0 nie licze bo o jest wektor wejscie!!!!!!!!!!!!!!!!!!!!!!!
    {
        for (int j = 0 ; j< iloscNeuronowNaWarstwe[i]; ++i) // dla kazdego neuronu z warstwy
        {
            double sumabledow = 0.0;
            for(int k = 0; k < iloscNeuronowNaWarstwe.size()-1; ++k)
            {
                sumabledow += (siecNeuronow[i+1][k] -> blad) * (siecNeuronow[i+1][k] ->wagi[j]);
            }
            siecNeuronow[i][j] -> blad = sumabledow;
        }
    }
    
    /// jeszcze dla warstwy wejsciowej
   for (int j = 0 ; j< iloscNeuronowNaWarstwe[0]; ++j) // dla kazdego neuronu z warstwy
        {
            double sumabledow = 0.0;
            for(int k = 0; k < iloscNeuronowNaWarstwe.size()-1; ++k)
            {
                sumabledow += (siecNeuronow[0][k] -> blad) * (siecNeuronow[0][k] ->wagi[j]);
            }
            wejscie[j] -> blad = sumabledow;
        }

}

void SiecNeuronow::algorytmPropagacjiWstecznej()
{
    
    for(int i = 0; i < wejscie.size(); ++i) // zmieniam wagi w wejsciu najpierw
    {
       // wejscie[i] -> waga[0] = wejscie[i] -> waga[0] + ETA * 
    }
    
}


//teraz trzeba zmieniac wagi razem z wagą biasu