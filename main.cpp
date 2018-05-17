
#include <iostream>

#include "headers/Matematyka.h"
//#include "headers/Losowanie.h"
#include "headers/Dane.h"
#include "headers/Menu.h"
#include "headers/SiecNeuronow.h"

int ILOSC_EPOK = 90000;

using namespace std;

int main() {

    srand(time(NULL));


    //cout << funkcjaAktywacji(10.0,1.0);

    //Dane dan(50);
    //int x;
    /*
    Losowanie l1(-0.5,0.5);
    Losowanie l2(0,50);
    vector<int> wekt(52,0);
    for (int i=0; i<20000; i++)
    {
        wekt[l2.losujInt()] += 1;
        cout <<l1.losujWagi() <<" ";
        if(i%20 ==0) cout <<endl;
        //     x =dan.losujInt();
        //if (x<1) cout << x <<" ";

    }
    for (int i=0; i< wekt.size(); i++)
        cout << i <<": "<<wekt[i] <<endl;

    cout <<"\nTeraz sprawdzam czy dobrze losuje"<<endl;

    Dane dan;
    vector<int> wylosowane = dan.wylosujKolejnoscPobierania(50);
    int suma=0, dodane = 0;
    for(int i =0; i < wylosowane.size(); i++)
    {
        suma += wylosowane[i];
        cout << wylosowane[i] << " ";
    }
    for(int i =0; i<50; i++) dodane +=i;

    cout <<"\n suma = " << suma <<"  Dodane = " <<dodane;
*/
    ///////////////////  PROGRAM

    vector<int> warstwy({4, 2, 3});
    SiecNeuronow siec(warstwy);

    Dane dane;
    dane.wczytajPlik();
    dane.normalizuj();
    dane.rozdzielDane(30, 10);

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
                if( 0 == epoka % 100 ) cout <<epoka<< " Blad Epoki: " << bladEpoki << endl;

                //if(epoka == 1) {siec.wypiszSiebie();cout<<"\n dupa\n";}
                epoka++;
                bladEpokiStary = bladEpoki;

            }
            cout << " KONIEC UCZENIA" << endl;

            siec.wypiszSiebie();
            cout << endl << endl;
            siec.wypiszBledy();

        }
        else
        {
            pierwszeMenu = false; // by juz nie pytal czy uczyć czy testowac

            cout << "\nTestuje na danych podanych w pliku, blende dane to 31 oraz 38" << endl;

            vector<int> kolejnosc = dane.wylosujKolejnoscPobierania(dane.ileDanychTestowych());

            menuNaglowek();

            double bladEpokiTestowania = 0.0;
            for (int i = 0; i < kolejnosc.size(); i++) {
                vector<double> wej = dane.pobierzWejscieTestowania(kolejnosc[i]);
                vector<double> wyj = dane.pobierzWyjscieTestowania(kolejnosc[i]);

                siec.testowanieSieci2(wej, wyj);
                bladEpokiTestowania += siec.bladSieci();

                //  if (kolejnosc[i] == 200) {

                // if (epoka % 500 == 0) {
                //    siec.wypiszRaz(wyj);
                // }

            }
            bladEpokiTestowania /= kolejnosc.size();
            cout <<  endl << "Blad Testowania wyniosl: " << bladEpokiTestowania;


            }
    }

    return 0;
}
