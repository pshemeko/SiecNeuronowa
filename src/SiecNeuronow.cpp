//
// Created by Przemo on 2018-05-16.
//

#include "../headers/SiecNeuronow.h"
#include "../headers/Matematyka.h"

SiecNeuronow::SiecNeuronow(vector<int> iloscNeuronowNaWarstweDomyslna ) // ilosc neuronow na arstwe to wektor ktory zawiera na kazdej pozycji ile neuronow jest w danej warstwie
        : iloscNeuronowNaWarstwe{iloscNeuronowNaWarstweDomyslna}
{
    // tworze warstwe rozprowadzajaca

    vector<Neuron*> rozprowadzajaca ;
    for (int i = 0; i < iloscNeuronowNaWarstwe[0]; ++i )
    {
        rozprowadzajaca.push_back( new Neuron(1,CZY_BIAS));
        rozprowadzajaca[i]-> wagi[0] = 1.0;   // bo warstwa wejsciowa jest tylko do rozprowadzenia sygnalu wiec tam wag nie ma
        rozprowadzajaca[i]-> wagi[1] = 0.0;   //TODO sprawdzic ale chyba w rozprowadzajacej nie ma biasu wiec jego wage zeruje
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

void SiecNeuronow::obliczanieWyjsciaNeuronow(vector<double> danaWej)
{
    //dla warstwy rozprowadzajacej
    for(int i = 0; i < iloscNeuronowNaWarstwe[0]; i++)
        siecNeuronow[0][i] -> wyjscie = danaWej[i];

    //dla sieci
    for(int i = 1; i < iloscNeuronowNaWarstwe.size(); ++i)
    {
        for(int j=0; j< iloscNeuronowNaWarstwe[i]; ++j)
        {
            double suma = 0.0;  // wyjscie z sumatora
            for(int k = 0; k< iloscNeuronowNaWarstwe[i-1]; ++k)
            {
                suma += siecNeuronow[i][j] -> wagi[k] * siecNeuronow[i-1][k] -> wyjscie;
            }
            siecNeuronow[i][j] -> wyjscie = funkcjaAktywacji(suma);
            //cout <<"\twyjscie: " << siecNeuronow[i][j] -> wyjscie;
        }
    }
}

void SiecNeuronow::obliczanieBledow(vector<double> danaWyj)
{
    // dla wyjsciowej
    int ostatnia = iloscNeuronowNaWarstwe.size() -1;
    for(int i = 0; i < iloscNeuronowNaWarstwe[ostatnia]; i++)
    {
        // popchodna jest obliczana na podstawie wartosci funkcji aktywacji neuronu (czyli wyjscia)
        siecNeuronow[ostatnia][i] ->blad = (danaWyj[i] - siecNeuronow[ostatnia][i] -> wyjscie) * pochodnaFunkcjiAktywacji(siecNeuronow[ostatnia][i] -> wyjscie);
    }

    //dla sieci - propagujc wstecz
    for(int i = ostatnia -1; i > 0; --i) // bo dla rozprowadzajacej nie robimy
    {
        for(int j = 0; j < iloscNeuronowNaWarstwe[i]; ++j)
        {
            double suma = 0.0;
            for (int k = 0; k < iloscNeuronowNaWarstwe[i + 1]; ++k) {
                suma += siecNeuronow[i][j]-> wagi[k] * siecNeuronow[i + 1][k] -> blad;
            }
            siecNeuronow[i][j]->blad = suma * pochodnaFunkcjiAktywacji(siecNeuronow[i][j] -> wyjscie);
        }
    }
}

void SiecNeuronow::ZmianaWagSieci()
{

    for(int i = 1; i < iloscNeuronowNaWarstwe.size(); ++i)
    {
        for(int j = 0; j < iloscNeuronowNaWarstwe[i]; ++j)
        {
            for(int k = 0; k < iloscNeuronowNaWarstwe[i-1]; ++k)
            {
                siecNeuronow[i][j] -> wagi[k] += ETA * siecNeuronow[i][j] -> blad * siecNeuronow[i-1][k] -> wyjscie;
                // gdy momentum wzor z danych mlodego
                siecNeuronow[i][j] -> wagi[k] += CZY_Z_MOMENTEM * MI * (ETA * siecNeuronow[i][j] -> blad * siecNeuronow[i-1][k] ->wyjscie);
            }
        }
    }

}

void SiecNeuronow::wypiszSiebie()
{
    cout <<endl << "TERAZ SIEC WYJSC:"<<endl;
    for(int i = 0; i<siecNeuronow.size(); i++)
    {


        for(int j = 0; j<siecNeuronow[i].size(); j++)
        {


            cout << siecNeuronow[i][j] -> wyjscie << "\t";
        }
        cout <<endl <<"warstwa ukryta: "<< i << endl;
    }

}


void SiecNeuronow::wypiszBledy(){
    cout <<endl << "TERAZ BLEDY"<<endl;
    for(int i = 0; i<siecNeuronow.size(); i++)
    {


        for(int j = 0; j<siecNeuronow[i].size(); j++)
        {


            cout << siecNeuronow[i][j] -> blad << "\t";
        }
        cout <<endl <<"warstwa ukryta: "<< i << endl;
    }

}

void SiecNeuronow::wypiszWagi()
{
    cout <<endl << "TERAZ WAGI"<<endl;
    for(int i = 0; i<siecNeuronow.size(); i++)
    {
    cout << endl<<"Warstwa["<<i<<"] ";

        for(int j = 0; j<siecNeuronow[i].size(); j++)
        {
            cout << endl << "Neuron["<<j<<"] wagi:";
            for(int k =0; k < siecNeuronow[i][j]->wagi.size();k++)
                cout << siecNeuronow[i][j] -> wagi[k] << "\t";
        }
        cout <<endl <<"warstwa ukryta: "<< i << endl;
    }
}