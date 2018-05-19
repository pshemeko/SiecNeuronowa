
#include <iostream>

#include "headers/Matematyka.h"
//#include "headers/Losowanie.h"
#include "headers/Dane.h"
#include "headers/Menu.h"
#include "headers/SiecNeuronow.h"

int ILOSC_EPOK = 100000;

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

    vector<int> warstwy({4, 4, 3, 3});

    // zapisywanie wynikow do pliku
    string nazwaU = "wynikiUczenie.txt";
    ofstream foutUczenie(nazwaU.c_str());
    string nazwaT = "wynikiTestowanie.txt";
    ofstream foutTestowanie(nazwaT.c_str());
    string nazwaW = "wynikiWalidacja.txt";
    ofstream foutWalidacja(nazwaW.c_str());

    ostringstream ss ;
    ss << "Zestaw badawczy nr. 1 Wspolczynnik nauki = " << ETA <<" Wspolczynnik momentum = " << MI << " ILOSC EPOK = " << ILOSC_EPOK << " Uklad warstw sieci: " ;
    for(int i = 0; i < warstwy.size()-1; i++ ) ss << warstwy[i] << "-";
    ss << warstwy[warstwy.size()-1] <<endl;

    foutUczenie  << ss.str();
    foutTestowanie << ss.str();
    foutWalidacja << ss.str();

    SiecNeuronow siec(warstwy);

    Dane dane;
    dane.wczytajPlik();
    dane.normalizuj();
    //dane.rozdzielDane(30, 10);
    dane.rozdzielDaneUstalonaKolejnosc();

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

                if( 0 == epoka % 100 )
                {
                    vector<int> kolejnoscTest = dane.wylosujKolejnoscPobierania(dane.ileDanychTestowych());

                    double bladEpokiTestowania = 0.0;
                    for (int i = 0; i < kolejnoscTest.size(); i++)
                    {
                        vector<double> wej2 = dane.pobierzWejscieTestowania(kolejnoscTest[i]);
                        vector<double> wyj2 = dane.pobierzWyjscieTestowania(kolejnoscTest[i]);

                        //siec.testowanieSieci2(wej2, wyj2);
                        siec.obliczanieWyjsciaNeuronow(wej2);
                        siec.obliczanieBledow(wyj2);
                        bladEpokiTestowania += siec.bladSieci();
                    }
                    //cout <<"dupa\n";
                    foutUczenie  << epoka << " " << bladEpoki << endl;
                    foutTestowanie << epoka << " " << bladEpokiTestowania << endl;
                }

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
            int ileWykryto = 0;
            for (int i = 0; i < kolejnosc.size(); i++) {
                vector<double> wej = dane.pobierzWejscieTestowania(kolejnosc[i]);
                vector<double> wyj = dane.pobierzWyjscieTestowania(kolejnosc[i]);

                int numer = siec.testowanieSieci2(wej, wyj);
                ileWykryto += numer;
                bladEpokiTestowania += siec.bladSieci();
                cout << numer;

                //  if (kolejnosc[i] == 200) {

                // if (epoka % 500 == 0) {
                //    siec.wypiszRaz(wyj);
                // }

            }
            bladEpokiTestowania /= kolejnosc.size();
            cout <<  endl << "Blad Testowania wyniosl: " << bladEpokiTestowania<<endl<<endl;
            cout << "Dobrze wykryto " << ileWykryto << "  kwiatkow" << " wszystkich bylo: " <<kolejnosc.size();


            }
    }


    foutUczenie.close();
    foutTestowanie.close();
    foutWalidacja.close();

    return 0;
}
