/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Przemo
 *
 * Created on 15 kwietnia 2018, 00:03
 */

#include <cstdlib>
#include <iostream>
#include "SiecNeuronow.h"
#include "Dane.h"

using namespace std;

static int ILOSCEPOK = 30000;
static double BLADOCZEKIWANY = 0.0001;
/*
 * 
 */
int main(int argc, char** argv) {

    SiecNeuronow siec;
    Dane dane(4);
    srand(time(NULL));


    // wyswietlam poczatek
    vector<double> tempy = dane.pobierzWejscie((0,1,2,3));
/*
    cout << "\tSIEC STARTUJE Z WARTOSCIAMI::"<<endl<<endl;
    for(int i = 0; i<siec.iloscNeuronowNaWarstwe[siec.iloscNeuronowNaWarstwe.size()-1]; i++)
    {
        cout << "\tWOczekiwano:" << tempy[i] ;
        // cout << siec.daneWyjsciowe[kolejnosc[kolejnosc.size()-1]][i];
        cout << "\tWyjscie: ";
        //cout << (siec.siecNeuronow[2][i])->wyjscie;
        cout << siec.siecNeuronow[1][i]->wyjscie ;
        cout << "\tWagi: ";
        for (int j=0; j<2;j++)
            cout << siec.siecNeuronow[1][i]->wagi[j] << "\t";
        cout<< endl;

    }
    cout <<endl;
    cout << "\tI OBLICZAMY::::::::::::::::::::::::::::::::::::::;::"<<endl<<endl;
*/

    while (ILOSCEPOK)
    {

        vector<int> kolejnosc = dane.wylosujKolejnoscPobierania();

        for(int i = 0; i < kolejnosc.size(); i++)
        {

            vector<double> tmp = dane.pobierzWejscie(kolejnosc[i]);

            siec.obliczanieWyjsciaNeuronow(tmp);
            siec.obliczanieBledow(tmp);
            siec.ZmianaWagSieci(tmp);

            // WYSWIETLANIE DANYCH WYBRANYCH
           // if(i == kolejnosc.size()-1)
            //manipulowanie wyswietlaniem
            ios_base::fmtflags old = cout.setf(ios_base::left, ios_base::adjustfield);
           cout.setf( ios_base::showpos); //pokazuje znak + zawsze

            if(kolejnosc[i] == 2)
            {
                if(ILOSCEPOK %500)
                {

                    for(int i = 0; i<siec.iloscNeuronowNaWarstwe[siec.iloscNeuronowNaWarstwe.size()-1]; i++)
                    {
                        cout.precision(12);
                        cout << "\tWOczekiwano:" << tmp[i] ;
                        cout << "\tWyjscie: ";
                        cout.width(17);
                        cout << siec.siecNeuronow[1][i]->wyjscie ;
                        cout << "\tWagi: ";
                        for (int j=0; j<2;j++){
                            cout.width(14);
                            cout << siec.siecNeuronow[1][i]->wagi[j] << "  ";
                        }
                        cout << "\tStareWagi: ";
                        for (int j=0; j<2;j++)
                        {
                            cout.width(14);
                            cout << siec.siecNeuronow[1][i]->stareWagi[j] << "\t";
                        }
                             cout<< endl;

                    }
                    cout <<endl;
                }
            }
             cout.setf(old, ios_base::adjustfield);// przywracam stare ustwaienia

        }

        ILOSCEPOK--;
    }

    cout <<" KONIEC UCZENIA"<<endl;


    return 0;
}

