
#include <iostream>
#include <iomanip>

#include "headers/Matematyka.h"
//#include "headers/Losowanie.h"
#include "headers/Dane.h"
#include "headers/Menu.h"
#include "headers/SiecNeuronow.h"

int ILOSC_EPOK = 1000;//100000;

using namespace std;

int main() {

    srand(time(NULL));

    ///////////////////  PROGRAM

    vector<int> warstwy({4, 3, 3});
    SiecNeuronow siec(warstwy);

    // zapisywanie wynikow do pliku
    string nazwaU = "Wykres_Bledu_Uczenie.txt";
    ofstream foutUczenie(nazwaU.c_str());
    string nazwaT = "Wykres_Bledu_Testowania.txt";
    ofstream foutTestowanie(nazwaT.c_str());
    string nazwaW = "wynikiWalidacja.txt";
    ofstream foutWalidacja(nazwaW.c_str());
    string nazwaWykryty = "wynikiWykrytychDanejEpoki.txt";
    ofstream foutWykrytych(nazwaWykryty.c_str());

    ostringstream opisEksperymentu ;
    opisEksperymentu << "Zestaw badawczy nr. 1 Wspolczynnik nauki = " << ETA <<" Wspolczynnik momentum = " << MI << " ILOSC EPOK = " << ILOSC_EPOK << " Uklad warstw sieci: " ;
    for(int i = 0; i < warstwy.size()-1; i++ ) opisEksperymentu << warstwy[i] << "-";
    opisEksperymentu << warstwy[warstwy.size()-1] <<endl;
    foutWalidacja << opisEksperymentu.str() << endl;
    foutWykrytych  << opisEksperymentu.str() << endl;

    Dane dane;
    dane.wczytajPlik();
    dane.normalizuj();
    //dane.rozdzielDane(30, 10);
    dane.rozdzielDaneUstalonaKolejnosc();


    //dane.wypiszWektorPar(dane.daneWszystkie);
    //dane.wypiszWektorPar(dane.daneUczenia);
    //dane.wypiszWektorPar(dane.daneTestowe);
    //dane.wypiszWektorPar(dane.daneWalidacyjne);

   // dane.rozdzielanieDlaWykresuZbiorow(); // potrzebowalem tylko raz aby rozdzielic zbior danych wej. i narysowac go na wykresie

    bool pierwszeMenu = true;

    while(pierwszeMenu)
    {
        menu();
        int wybor;
        cin >> wybor;

        if (wybor == 1) {    // nauka

            int epoka = 0;

            //siec.wypiszSiebie();
            //cout << endl << endl;
            //siec.wypiszBledy();
            double bladEpokiStary = 0.0;
            while (epoka < ILOSC_EPOK) {

                vector<int> kolejnosc = dane.wylosujKolejnoscPobierania(dane.ileDanychUczenia());
                double bladEpoki = 0.0;
                for (int i = 0; i < kolejnosc.size(); i++) {
                    vector<double> wej = dane.pobierzWejscieUczenia(kolejnosc[i]);
                    vector<double> wyj = dane.pobierzWyjscieUczenia(kolejnosc[i]);

                    siec.obliczanieWyjsciaNeuronow(wej);
                    siec.obliczanieBledow(wyj);
                    siec.ZmianaWagSieci();
                    bladEpoki += siec.bladSieci();

                    //  if (kolejnosc[i] == 200) {

                   // if (epoka % 500 == 0) {
                    //    siec.wypiszRaz(wyj);
                   // }

                }
                bladEpoki /= kolejnosc.size();


               // if( bladEpoki>bladEpokiStary ) cout << "Epoka: "<<epoka<< " blad wzrosl\t" << bladEpoki << "\t stary blad:" <<bladEpokiStary<<endl;

                //if( 0 == epoka % 100 ) cout <<epoka<< " Blad Epoki: " << bladEpoki << endl;

                //if( 0 == epoka % 100 )
                {
                    vector<int> kolejnoscTest = dane.wylosujKolejnoscPobierania(dane.ileDanychTestowych());

                    double bladEpokiTestowania = 0.0;
                    int ileWykrytoWEpoce = 0;
                    for (int i = 0; i < kolejnoscTest.size(); i++)
                    {
                        vector<double> wej2 = dane.pobierzWejscieTestowania(kolejnoscTest[i]);
                        vector<double> wyj2 = dane.pobierzWyjscieTestowania(kolejnoscTest[i]);

                        //siec.testowanieSieci2(wej2, wyj2);
                        siec.obliczanieWyjsciaNeuronow(wej2);
                        siec.obliczanieBledow(wyj2);
                        bladEpokiTestowania += siec.bladSieci();
                        // zliczam dane ile wykryto dobrze
                        int oczekiwany = 0;
                        int wykryty = 0;
                        for (int i = 0; i < wyj2.size(); ++i)
                            if (1.0 == wyj2[i]) oczekiwany = i + 1;
                        wykryty = siec.ktoryWykryto();
                        if ( wykryty == oczekiwany) ileWykrytoWEpoce++;
                    }
                    //cout <<"dupa\n";
                    foutUczenie  << epoka << " " << bladEpoki << endl;
                    foutTestowanie << epoka << " " << bladEpokiTestowania << endl;
                    foutWykrytych << epoka << " " << ileWykrytoWEpoce <<endl;
                    if( 0 == epoka % 100 ) cout <<epoka<< " Blad Epoki w Testowaniu: " << bladEpokiTestowania << endl;

                }

                //if(epoka == 1) {siec.wypiszSiebie();cout<<"\n dupa\n";}
                epoka++;
                bladEpokiStary = bladEpoki;

            }
            cout << " KONIEC UCZENIA" << endl;

            siec.wypiszSiebie();
            cout << endl << endl;
            siec.wypiszBledy();

            siec.wypiszWagi(foutWalidacja);

        }
        else
        {
            pierwszeMenu = false; // by juz nie pytal czy uczyć czy testowac

            vector<int> kolejnosc = dane.wylosujKolejnoscPobierania(dane.ileDanychTestowych());

            //menuNaglowek();
            foutWalidacja << endl << "Teraz wyniki pogramu na danych walidacyjnych:" << endl << endl;

            double bladEpokiTestowania = 0.0;
            int ileWykryto = 0;
            for (int i = 0; i < kolejnosc.size(); i++) {
                vector<double> wej = dane.pobierzWejscieTestowania(kolejnosc[i]);
                vector<double> wyj = dane.pobierzWyjscieTestowania(kolejnosc[i]);
                double bladDanych = 0.0;

                ostringstream s1;
                // int numer=0;
                    {
                        s1 << "[ ";
                        for (int i = 0; i < wej.size(); ++i) {
                            // teraz cofam normalizacje
                            double wejscie = wej[i] * ( dane.maksima[i] - dane.minima[i] )  + dane.minima[i];
                            wejscie = round(wejscie * 100) / 100;

                            s1 << wejscie << "   ";
                        }
                        s1 << " ] - wejscie sieci" << endl << "[ ";
                        //foutWalidacja << s1.str();
                     }
                s1 << siec.testowanieSieci2(wej, wyj, ileWykryto, dane.minima, dane.maksima);


               // ileWykryto += numer;
                bladDanych = siec.bladSieci();
                bladEpokiTestowania +=bladDanych;

               s1 << "Błąd sieci przy tych danych wyniósł: " << bladDanych <<endl<<endl;

                foutWalidacja <<  s1.str();
                cout << s1.str();

            }
            bladEpokiTestowania /= kolejnosc.size();

            ostringstream stmp;

            stmp <<  endl << "Globalny blad danych walidacji wyniosl: " << bladEpokiTestowania << endl << endl;
            stmp << "Dobrze wykryto " << ileWykryto << "  kwiatkow" << " wszystkich bylo: " << kolejnosc.size() << endl;

            cout << stmp.str();
            foutWalidacja << stmp.str();
            }
    }

    foutUczenie  << opisEksperymentu.str();
    foutTestowanie << opisEksperymentu.str();


    foutUczenie.close();
    foutTestowanie.close();
    foutWalidacja.close();

    return 0;
}
