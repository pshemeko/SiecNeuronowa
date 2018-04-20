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

SiecNeuronow::SiecNeuronow(vector<int> iloscNeuronowNaWarstwe2)//, int neuronowNaKazdejWarstwieUkrytej)
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
            
            //if(j = 1) {  // jesli jest to warstwa 1 czyli pierwsza za wejsciowa to musi pobierac dane z warstwy wejsciowej
                        //Neuron neuronik =  Neuron(ILOSCWEJSC,CZY_BIAS);
            //            warstwa.push_back(new Neuron(iloscNeuronowNaWarstwe[j-1],CZY_BIAS));
            //            }
            //else {
                //Neuron neuronik =  Neuron(iloscNeuronowNaWarstwe[j-1],CZY_BIAS);
            warstwa.push_back(new Neuron(iloscNeuronowNaWarstwe[j-1],CZY_BIAS));
            //}
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
void SiecNeuronow::obliczanieWyjsciaNeuronow(vector<double> danaWej) // SPRAWDZAC CZY ILOSC ELEMENTOW daneWej JEST TAKA JAK WIELKOSC WARSTWY POCZATKOWEJ
{
/*
    for (int i =0; i<danaWej.size();i++)
        std::cout <<danaWej[i];
    std::cout <<std::endl;
*/
    // podawanie danych na warstwe wejsciowa
    for(unsigned int i = 0; i < iloscNeuronowNaWarstwe[0]; ++i)
    {


       // double wartosc222 = danaWej[i] *( wejscie[i]->wagi[0]);
       // std::cout << "co tu kuwa nie dziala" << wartosc222<<std::endl;
        double wartosc = danaWej[i] * (wejscie[i]->wagi[0]) + CZY_BIAS * wejscie[i]->wagi[1]; // bias jest ostatnim elem w wektorze
        //std::cout << " wejscie biasu: " << wejscie[i]->wagi[1] <<std::endl;
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
        //TODO ZMIENIC CHYBA!!!!!!!!!!!!!!! NIE NIE, TO JEST DOBRZE - zerknij algorytm propagacji wstecznej lub rozpisz na kartce
    {
        for(int j = 0; j < iloscNeuronowNaWarstwe[i]; ++j) // dla kazdego neuronu w tej warstwie licze jego wyjscie
        {
            double suma = 0.0;
            for(int k = 0; k < iloscNeuronowNaWarstwe[i-1]; ++k)
            {
                suma += siecWyjsc[i-1][k] * (siecNeuronow[i-1][j]->wagi[k] );
            }
            suma += CZY_BIAS * siecNeuronow[i-1][j]->wagi[iloscNeuronowNaWarstwe[i-1]];   // gdy bias to trzeba go jeszcze dodac i przemnozyc przez jego wagee
                                                                // waga biasu jest ostatnia w wektorze wag zawze jest o jedna waga wiecej w neuonie gdyby bias byl
            siecNeuronow[i-1][j]->setWyjscie(suma);
            siecWyjsc[i][j] = siecNeuronow[i-1][j]->wyjscie;

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

vector<int> SiecNeuronow::losujeKolejnosc(int iloscWektorowZDanymi)
{
    vector<int> wylosowane;
    // zmienic to potem i dac do klasy losowanie
    

    int liczba = rand() % 199; //199 liczba pierwsza
    int kierunek = rand() % 100;
    if (kierunek %2)
    {
        for (int i=0; i<iloscWektorowZDanymi; i++)
        {
            wylosowane.push_back(liczba%iloscWektorowZDanymi );
            liczba++;
        }
    }
    else
    {
        for (int i=0; i<iloscWektorowZDanymi; i++)
        {
            wylosowane.push_back(liczba%iloscWektorowZDanymi );
            if(0 == liczba) liczba = iloscWektorowZDanymi;
            liczba--;
        }
    }
    
    return wylosowane;
}


void SiecNeuronow::obliczanieBledow(vector<double> danaWyj)
{
    int ostWarstwa = iloscNeuronowNaWarstwe.size() - 1;
    //dla kazdego neuronu w warstwie wyjsciowej obliczam jego blad a potem poopaguje te bledy wtecz
    for(int i = 0; i < iloscNeuronowNaWarstwe[ostWarstwa]; ++i)
    {
        siecNeuronow[ostWarstwa-1][i] -> blad = danaWyj[i] - (siecNeuronow[ostWarstwa-1][i] -> wyjscie) ;
    }


    // teraz trzeba propagowac wstecz
    for (int i = iloscNeuronowNaWarstwe.size() - 2; i > 0; --i) // dla 0 nie licze bo o jest wektor wejscie!!!!!!!!!!!!!!!!!!!!!!!
    {
        for (int j = 0 ; j< iloscNeuronowNaWarstwe[i]; ++j) // dla kazdego neuronu z warstwy
        {
            double sumabledow = 0.0;
            for(int k = 0; k < iloscNeuronowNaWarstwe[i+1]; ++k)
            {
                sumabledow += (siecNeuronow[i][k] -> blad) * (siecNeuronow[i][k] ->wagi[j]);
            }

            siecNeuronow[i-1][j] -> blad = sumabledow;
        }
        //cout<<endl;
    }


    /// jeszcze dla warstwy wejsciowej
   for (int j = 0 ; j< iloscNeuronowNaWarstwe[0]; ++j) // dla kazdego neuronu z warstwy
        {
            double sumabledow = 0.0;
            for(int k = 0; k < iloscNeuronowNaWarstwe[1]; ++k)
            {
                sumabledow += (siecNeuronow[0][k] -> blad) * (siecNeuronow[0][k] ->wagi[j]);
            }
            wejscie[j] -> blad = sumabledow;
        }


}

// zmienia nam wagi w sieci neuronowej
void SiecNeuronow::ZmianaWagSieci(vector<double> daneWej) // dane wej to sa dane wejsciowe do uczenia w danym i-tym obrocie epoki
{
    // zmiana wag dla warstwy wejsciowej

    for(int i = 0; i < wejscie.size(); ++i) // zmieniam wagi w wejsciu najpierw
    {
        //przeniesc te funkcje do neuronu ( zrob w neuronie funkcje zmien wage()
        wejscie[i] -> przepiszDoStarejWagi();
        //wejscie[i] -> stareWagi[0] = wejscie[i] -> wagi[0];
        double tmpwaga = (wejscie[i] -> stareWagi[0]);
        double liczba = ETA * wejscie[i]->blad;
        double pochodna = ( wejscie[i] -> pochodnaFunkcjiAktywacji( wejscie[i]-> wyjscieSumatora));
        double wej = daneWej[i] ;
        double uuu = liczba *pochodna*wej;
        tmpwaga +=uuu + ZMOMENTEM * ALFHA * (wejscie[i] ->wagi[0] - wejscie[i] -> stareWagi[0]);//TODO albo +

        wejscie[i] -> wagi[0] = tmpwaga;
        //cout<<"\nstarea:"<< wejscie[i] -> stareWagi[0] <<" eta:"<<ETA<<" blad:"<<wejscie[i]->blad <<" Pochodna:"<<wejscie[i] -> pochodnaFunkcjiAktywacji( wejscie[i]-> wyjscieSumatora)<<" Danawej:"<<daneWej[i] ;
        //    cout<<" obliczylem wage: " <<tmpwaga<< " nowa waga:" <<wejscie[i] -> wagi[0] << " stara waga:" <<wejscie[i] -> stareWagi[0];
        //bias
        if(CZY_BIAS)
        {
           // wejscie[i] -> stareWagi[1] = wejscie[i] -> wagi[1];
            wejscie[i] -> wagi[1] = (wejscie[i] -> stareWagi[1]) + ETA * wejscie[i]->blad * ( wejscie[i] -> pochodnaFunkcjiAktywacji( wejscie[i]-> wyjscieSumatora)) * wejscie[i]->wartoscBiasu ;
            wejscie[i] -> wagi[1] += ZMOMENTEM * ALFHA* (wejscie[i] ->wagi[1] - wejscie[i] -> stareWagi[1]);
        }
    }


    // zmiana wag dla 0-wej warstwy  ukrytej gdyz ta pobiera wartosci z warstwy wejsciowej
    
     for(int i = 1; i < iloscNeuronowNaWarstwe.size() ; ++i) // i - numer warstwy ukrytej od zera bo te dane sa w wektrorze w ktorym 0 pokazuje ile jest neuronow w warstwie wejsciowej
     {

         for (int j = 0; j<iloscNeuronowNaWarstwe[i]; ++j) // j -  ilosc neuronow w warstwie ukrytej
         {
             siecNeuronow[i-1][j]->przepiszDoStarejWagi();
             //cout << "\tPRZEPISALEM WAGI["<<i-1<<"]["<<j<<"]: :" << siecNeuronow[i-1][j]->wypisz()<<endl;
             double PochodnaAktywacjiWyjsciaSumatora = siecNeuronow[i-1][j] -> pochodnaFunkcjiAktywacji( siecNeuronow[i-1][j]-> wyjscieSumatora);

             double blad = siecNeuronow[i-1][j]->blad;
             double staleDlaNeuronu = ETA * blad * PochodnaAktywacjiWyjsciaSumatora;
             for(int k = 0; k < iloscNeuronowNaWarstwe[i-1]; ++k)
             {

                // siecNeuronow[i-1][j] -> stareWagi[k] = siecNeuronow[i-1][j] -> wagi[k];
                 //siecNeuronow[i-1][j] -> wagi[k] -= ETA * siecNeuronow[i-1][j]->blad *PochodnaAktywacjiWyjsciaSumatora* siecWyjsc[i-1][k];//daneWej[i] ; // TODO sprawdzic czy nie minus w wykladzie
                 double wejscie = staleDlaNeuronu * siecWyjsc[i-1][k];
                 siecNeuronow[i-1][j] -> wagi[k] = siecNeuronow[i-1][j]->stareWagi[k] + wejscie + ZMOMENTEM * ALFHA *(siecNeuronow[i-1][j]->wagi[k] - siecNeuronow[i-1][j]->stareWagi[k] );

             //    cout << "\twaga stara["<<i-1<<"]["<<j<<"]:"  <<siecNeuronow[i-1][j]->stareWagi[i]<< "\twaga nowa:" <<siecNeuronow[i-1][j]->wagi[i];
             }
            // cout<<" Wyjscie sumatora ["<<i-1<<"]["<<j<<"]:" << siecNeuronow[i-1][j]->wyjscieSumatora << " Wyjscie :" << siecNeuronow[i-1][j]->wyjscie;
            // cout<<endl;
             if(CZY_BIAS)
             {
                 //cout<<"Jeszcze BIAS: " <<endl;
                 // todo czy dobrze????

                 //siecNeuronow[i-1][j] -> wagi[iloscNeuronowNaWarstwe[i-1]] -= ETA * siecNeuronow[i-1][j]->blad * PochodnaAktywacjiWyjsciaSumatora * siecNeuronow[i-1][j]->wartoscBiasu;
                 siecNeuronow[i-1][j] -> wagi[iloscNeuronowNaWarstwe[i-1]]  += staleDlaNeuronu * siecNeuronow[i-1][j]->wartoscBiasu + ZMOMENTEM * ALFHA *(siecNeuronow[i-1][j]->wagi[iloscNeuronowNaWarstwe[i-1]] - siecNeuronow[i-1][j]->stareWagi[iloscNeuronowNaWarstwe[i-1]] );

             }
             //cout << endl;
         }

     }
    
    
}

double SiecNeuronow::bladCalkowity()
{
    double bladCaly = 0.0;
    for(int i = 0; i < wejscie.size(); ++i) 
       bladCaly += wejscie[i] -> blad;
    
    
     for(int i = 1; i < iloscNeuronowNaWarstwe.size() - 1; ++i) // i - numer warstwy ukrytej od zera bo te dane sa w wektrorze w ktorym 0 pokazuje ile jest neuronow w warstwie wejsciowej
     {
         for (int j = 0; iloscNeuronowNaWarstwe[i]; ++j) // j -  ilosc neuronow w warstwie ukrytej
         {
             bladCaly += siecNeuronow[i-1][j]->blad;
         }
     }
    
}