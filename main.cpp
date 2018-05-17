
#include <iostream>

#include "headers/Matematyka.h"
//#include "headers/Losowanie.h"
#include "headers/Dane.h"
#include "headers/Menu.h"
#include "headers/SiecNeuronow.h"

int ILOSC_EPOK = 7;

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



    vector<int> warstwy({4,2,4});
    SiecNeuronow siec(warstwy);
    Dane dane;
    int epoka = 0;

    dane.wczytajPlik();
    dane.normalizuj();
    dane.rozdzielDane(30,10);

    siec.wypiszSiebie();
    cout <<endl<<endl;
    siec.wypiszBledy();

    while(epoka < ILOSC_EPOK)
    {
        vector<int> kolejnosc = dane.wylosujKolejnoscPobierania(dane.ileDanychUczenia());
        double bladEpoki = 0.0;
        cout << "DUPA FUPA "<<kolejnosc.size()<< " ile danych uczenia" <<dane.ileDanychUczenia()<<endl;
        for (int i = 0; i < kolejnosc.size(); i++)
        {
            vector<double> wej = dane.pobierzWejscieUczenia(kolejnosc[i]);
            vector<double> wyj = dane.pobierzWyjscieUczenia(kolejnosc[i]);
            cout<<endl<<"Obliczanie wyjscia Neuronow"<<endl;
            siec.obliczanieWyjsciaNeuronow(wej);
            cout<<endl<<"obliczanie bledow"<<endl;
            siec.obliczanieBledow(wyj);
            siec.ZmianaWagSieci();
            bladEpoki += siec.bladSieci();

        }
        cout << "blad epoki"<< bladEpoki <<endl;

    epoka ++;
    }
    cout<<endl<<"OSTATNIE wypisy: " <<endl;
siec.wypiszSiebie();
    cout <<endl<<endl;
    siec.wypiszBledy();
    siec.wypiszWagi();

    return 0;
}