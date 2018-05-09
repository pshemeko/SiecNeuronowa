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
#include <fstream>
#include <cstdlib>
#include "SiecNeuronow.h"
#include "Dane.h"
#include <algorithm>

using namespace std;

int ILOSCEPOK = 70000;
double BLADOCZEKIWANY = 0.000000013;
/*
 * 
 */
int main(int argc, char** argv) {

    SiecNeuronow siec({4,10,10,3});

    Dane dane(150);   // losuje z 150 elementow wektroraPar danych wejsciowych
    srand(time(NULL));
    //do pliku
    string nazwa = "dane.txt";
    ofstream fout(nazwa.c_str());   // do wypisywania danych

    // wyswietlam poczatek jest blad
    //vector<double> tempy = dane.pobierzWejscie((0,1,2,3));


bool pierwszeMenu = true;
    while(pierwszeMenu) {

        dane.menu();
        int wybor;
        cin >> wybor;

        if (wybor == 1) {    // nauka

            dane.wczytajPlik("iris.data", 150);
            int ktoraEpoka = 0;
            while (ktoraEpoka < ILOSCEPOK) {

                vector<int> kolejnosc = dane.wylosujKolejnoscPobierania();
                double bladEpoki = 0.0;
                //vector<int> num = kolejnosc;
                //sort(num.begin(),num.end());
                //cout <<endl;
                for (int i = 0; i < kolejnosc.size(); i++) {

                    //cout << num[i]<< ":" <<kolejnosc[i] << " - ";

                    vector<double> wej = dane.pobierzWejscie(kolejnosc[i]);
                    vector<double> wyj = dane.pobierzWyjscie(kolejnosc[i]);

                    siec.obliczanieWyjsciaNeuronow(wej);
                    siec.obliczanieBledow(wyj);
                    siec.ZmianaWagSieci(wej);
                    bladEpoki += siec.obliczBladDlaWzorca(wyj);


                    //manipulowanie wyswietlaniem
                    ios_base::fmtflags old = cout.setf(ios_base::left, ios_base::adjustfield); // cout.setf( ios_base::showpos); //pokazuje znak + zawsze

                    //Wyswietlanie
                    if (kolejnosc[i] == 200) {
                        if (ktoraEpoka % 500 == 0) {
                            cout << endl;
                            for (int i = 0;
                                 i < siec.iloscNeuronowNaWarstwe[siec.iloscNeuronowNaWarstwe.size() - 1]; i++) {
                                cout.precision(12);
                                cout << "\tWart oczekiwana:" << wyj[i];
                                cout << "\tWyjscie: ";
                                cout.width(17);
                                cout << siec.siecNeuronow[siec.iloscNeuronowNaWarstwe.size() - 2][i]->wyjscie;
                                cout << "\tWagi: ";
                                for (int j = 0; j < siec.iloscNeuronowNaWarstwe[siec.iloscNeuronowNaWarstwe.size() - 2]; j++) {
                                    cout.width(16);
                                    cout << siec.siecNeuronow[siec.iloscNeuronowNaWarstwe.size() - 2][i]->wagi[j] << "  ";
                                }
                                cout << "\tStareWagi: ";
                                for (int j = 0; j < siec.iloscNeuronowNaWarstwe[siec.iloscNeuronowNaWarstwe.size() - 2]; j++) {
                                    cout.width(14);
                                    cout << siec.siecNeuronow[siec.iloscNeuronowNaWarstwe.size() - 2][i]->stareWagi[j] << "\t";
                                }
                                cout << endl;
                            }
                        }
                    }
                    cout.setf(old, ios_base::adjustfield);// przywracam stare ustwaienia

                }

                bladEpoki = bladEpoki / (double) (kolejnosc.size() - 1);

                if (ktoraEpoka % 100 == 0)
                    fout << ktoraEpoka << ";" << bladEpoki << endl;

                if (ktoraEpoka % 500 == 0) {
                    cout << "NUMER epoki: " << ktoraEpoka << " Blad sieci: " << bladEpoki << " Blad zadany:" << BLADOCZEKIWANY << endl;
                    if (abs(bladEpoki) < BLADOCZEKIWANY) {
                        cout << "Osiagnieto zalozony blad " << endl << "NUMER epoki: " << ktoraEpoka << " Blad sieci: "
                             << bladEpoki << endl;
                       //break;
                    }
                }
                ktoraEpoka++;
            }

            cout << " KONIEC UCZENIA" << endl;
        } else {
            pierwszeMenu = false; // by juz nie pytal czy uczyć czy testowac
            // dane.menuTestowanie();

            cout << "\nTestuje na danych podanych w pliku, blende dane to 31 oraz 38" << endl;

            dane.wczytajPlik("bezdekIris.data", 150);

            //vector<int> kolejnosc = dane.wylosujKolejnoscPobierania();
            vector<int> kolejnosc;
            for(int i = 0; i<150; i++)
            kolejnosc.push_back(i);


            dane.menuNaglowek();

            for (int i = 0; i < kolejnosc.size(); i++) {

                cout << "dana[" << kolejnosc[i]+1 << "]";
                vector<double> wej = dane.pobierzWejscie(kolejnosc[i]);
                vector<double> wyj = dane.pobierzWyjscie(kolejnosc[i]);

               // siec.obliczanieWyjsciaNeuronow(wej);
               // siec.obliczanieBledow(wyj);
                //siec.ZmianaWagSieci(wej);
                //bladEpoki += siec.obliczBladDlaWzorca(wyj);

                //vector <double> tes = {0.0, 0.0, 0.0 , 1.0};

                siec.testowanieSieci2(wej, wyj);


            }
            /*
             bool koniec = true;
             while(koniec)
             {
                   // dane.menuTestowanie();


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
        */

        }

    }
    return 0;
}

