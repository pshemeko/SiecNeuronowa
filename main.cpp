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
#include <cstdlib>
#include "SiecNeuronow.h"
#include "Dane.h"

using namespace std;

int ILOSCEPOK = 30000;
double BLADOCZEKIWANY = 0.00013;
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

bool pierwszeMenu = true;
    while(pierwszeMenu)
    {

    dane.menu();
    int wybor;
    cin >>wybor;

     if(wybor ==1) {
         int ktoraEpoka = 0;
         while (ktoraEpoka < ILOSCEPOK) {

             vector<int> kolejnosc = dane.wylosujKolejnoscPobierania();
             double bladEpoki = 0.0;
             for (int i = 0; i < kolejnosc.size(); i++) {

                 vector<double> tmp = dane.pobierzWejscie(kolejnosc[i]);

                 siec.obliczanieWyjsciaNeuronow(tmp);
                 siec.obliczanieBledow(tmp);
                 siec.ZmianaWagSieci(tmp);
                 bladEpoki += siec.obliczBladDlaWzorca(tmp);

                 // WYSWIETLANIE DANYCH WYBRANYCH
                 // if(i == kolejnosc.size()-1)
                 //manipulowanie wyswietlaniem
                 ios_base::fmtflags old = cout.setf(ios_base::left, ios_base::adjustfield);
                 // cout.setf( ios_base::showpos); //pokazuje znak + zawsze

                 if (kolejnosc[i] == 2) {
                     if (ktoraEpoka % 500 == 0) {

                         for (int i = 0; i < siec.iloscNeuronowNaWarstwe[siec.iloscNeuronowNaWarstwe.size() - 1]; i++) {
                             cout.precision(12);
                             cout << "\tWOczekiwano:" << tmp[i];
                             cout << "\tWyjscie: ";
                             cout.width(17);
                             cout << siec.siecNeuronow[1][i]->wyjscie;
                             cout << "\tWagi: ";
                             for (int j = 0; j < 2; j++) {
                                 cout.width(14);
                                 cout << siec.siecNeuronow[1][i]->wagi[j] << "  ";
                             }
                             cout << "\tStareWagi: ";
                             for (int j = 0; j < 2; j++) {
                                 cout.width(14);
                                 cout << siec.siecNeuronow[1][i]->stareWagi[j] << "\t";
                             }
                             cout << endl;

                         }
                         cout << endl;


                     }
                 }
                 cout.setf(old, ios_base::adjustfield);// przywracam stare ustwaienia

             }

             bladEpoki = bladEpoki / (double) (kolejnosc.size() - 1);
             if (ktoraEpoka % 500 == 0) {
                 cout << "NUMER epoki: " << ktoraEpoka << " Blad sieci: " << bladEpoki << endl;
                 if (bladEpoki < BLADOCZEKIWANY) break;
             }
             ktoraEpoka++;
         }

         cout << " KONIEC UCZENIA" << endl;
     } else
     {
         pierwszeMenu = false; // by juz nie pytal czy uczyć czy testowac
        // dane.menuTestowanie();
         bool koniec = true;


         while(koniec)
         {
                dane.menuTestowanie();
             int wybor;
             cin >>wybor;
                system("pause");
                system("clear");

                //cout << " Testowanie:" << endl;

             vector<double> tes;

             switch(wybor)
                {
                    case 0:
                        tes = dane.pobierzWejscie(0);
                    break;
                    case 1:
                        tes = dane.pobierzWejscie(1);
                    break;
                    case 2:
                        tes = dane.pobierzWejscie(2);
                    break;
                    case 3:
                        tes = dane.pobierzWejscie(3);
                    break;
                    case 5:
                        koniec = false;
                        break;
                    default:
                        throw "NIepoprawna wartosc nie ma tylu wektorow WYJjsciowych!!!!!!!!!!!!!!!!!!!!!!!/n\n";
                    break;

                }



             //vector <double> tes = {0.0, 0.0, 0.0 , 1.0};
             siec.testowanieSieci(tes, tes);


         }

     }

 }

    return 0;
}

