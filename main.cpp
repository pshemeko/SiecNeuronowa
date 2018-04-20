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

    /*
    vector<int> sprawdzam = dane.wylosujKolejnoscPobierania();

    for (int i =0; i< sprawdzam.size(); i++)
            cout<<sprawdzam[i]<< " ";
cout<<endl;
    vector<int> sprawdzam2 = dane.wylosujKolejnoscPobierania();
    for (int i =0; i< sprawdzam2.size(); i++)
        cout<<sprawdzam2[i]<< " ";
cout<<endl;
    vector<int> sprawdzam3 = dane.wylosujKolejnoscPobierania();
    for (int i =0; i< sprawdzam3.size(); i++)
        cout<<sprawdzam3[i]<< " ";
    cout<<endl;
    vector<int> sprawdzam4 = dane.wylosujKolejnoscPobierania();
    for (int i =0; i< sprawdzam4.size(); i++)
        cout<<sprawdzam4[i]<< " ";
    */
    // poko co tylko robie ilosc epok
    // dodac kryterium while blad < od bledu zadanego
    
    /*for(int j = 0; j<15; j++)
    {
    vector<int> kolejnosc = siec.losujeKolejnosc(4);
    
    for (int i=0; i<kolejnosc.size(); i++)
        cout << kolejnosc[i] << " ";
    
    cout << endl;
    }
     */

    // wyswietlam poczatek
    vector<double> tempy = dane.pobierzWejscie((0,1,2,3));
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


    while (ILOSCEPOK)
    {
        //vector<int> kolejnosc = siec.losujeKolejnosc(4);
        vector<int> kolejnosc = dane.wylosujKolejnoscPobierania();
        // sprawdzam lostowanie
    //    std::cout<<"wylosowano kolejnosc: ";
    //    for(int i=0; i< kolejnosc.size(); i++) printf( "Liczba : %d ", kolejnosc[i] );

        for(int i = 0; i < kolejnosc.size(); i++)
        {

     //       cout<<"\nwyswietlam wejscie kolejnosci nr:" << kolejnosc[i] << "  jego wektor (wartosc) to: ";
            vector<double> tmp = dane.pobierzWejscie(kolejnosc[i]);
            //for(int j=0; j<tmp.size();j++) cout <<tmp[j];
             //cout<<endl;
        //vector<int> * dane = siec.daneWyjsciowe[1];
        //for(int j=0; j<4;j++) cout <<&&dane[j];



            siec.obliczanieWyjsciaNeuronow(tmp);

            siec.obliczanieBledow(tmp);
            siec.ZmianaWagSieci(tmp);


           // if(i == kolejnosc.size()-1)
            if(kolejnosc[i] == 2)
            {
                if(ILOSCEPOK %500)
                {
                    for(int i = 0; i<siec.iloscNeuronowNaWarstwe[siec.iloscNeuronowNaWarstwe.size()-1]; i++)
                    {
                        cout.precision(12);
                        cout << "\tWOczekiwano:" << tmp[i] ;
                        // cout << siec.daneWyjsciowe[kolejnosc[kolejnosc.size()-1]][i];
                        cout << "\tWyjscie: ";
                        //cout << (siec.siecNeuronow[2][i])->wyjscie;
                        cout.width(17);
                        cout << siec.siecNeuronow[1][i]->wyjscie ;
                        cout << "\tWagi: ";
                        for (int j=0; j<2;j++){
                            cout.width(14);
                            cout << siec.siecNeuronow[1][i]->wagi[j] << " ";
                        }
                        cout << "\tStareWagi: ";
                        for (int j=0; j<2;j++)
                            cout << siec.siecNeuronow[1][i]->stareWagi[j] << "\t";
                        //cout<< endl;
                             cout<< endl;

                    }
                    cout <<endl;
                }
            }

/*
            // wypisze neurony
            cout <<"\nWEJSCIA:"<<endl;
            for(int i = 0; i<siec.wejscie.size();i++)
            {
                cout <<"Wejscie["<<i<<"]:" << siec.wejscie[i]->wypisz();
            }

            cout <<"\nWARSTWY UKRYTE I WYJSCIE:"<<endl;
            for(int i = 0; i<siec.siecNeuronow.size();i++)
            {
                for(int k = 0; k < siec.siecNeuronow[i].size(); k++)
                {
                    cout << "Neuron["<<i<<"][" <<k<<"]:" <<  siec.siecNeuronow[i][k]->wypisz() <<endl;
                }

            }

*/
        }
    


   // cout <<endl;
        
        ILOSCEPOK--;
    }
    

    //cin.get();
    cout <<" KONIEC KONIEC KONIEC" <<endl;
    system("pause");
    return 0;
}

