//
// Created by pobi on 5/14/18.
//

#ifndef KWIATKI_DANE_H
#define KWIATKI_DANE_H

#include <vector>

#include <random>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Losowanie.h"

typedef std::vector<std::pair< std::vector<double>, std::vector<double> > > VEKTORPAR;

using namespace std;

class Dane {

    //uniform_real_distribution<> dist;
    //uniform_int_distribution<> liczbaNaturalna; // losujemy int od 0 do ileLiczb(z konstruktora)
    //mt19937 gen;
public:
    VEKTORPAR daneWszystkie; // 50 pierwsszegych kwiatkow, potem 50 druich potem trzecich
    VEKTORPAR daneUczenia;
    VEKTORPAR daneTestowe;
    VEKTORPAR daneWalidacyjne;



    vector<double> maksima; // do normalizacji maksymalne wartosci danej zmiennej
    vector<double> minima;  // do normalizacji
   // int ileLiczb;

    //Dane(int ileLiczbLosowac);
    Dane() = default;
    virtual ~Dane();
    int ileDanychUczenia()      {return daneUczenia.size();     };
    int ileDanychTestowych()    {return daneTestowe.size();     };
    int ileDanychWalidacyjnych(){return daneWalidacyjne.size(); };

    vector<int> wylosujKolejnoscPobierania(int ileLiczb); // losuje kolejnosc liczb z przedz. [0, ileliczb) bez ileLiczb

    void wczytajPlik(string nazwaPliku = "iris.data", int ilosclinii = 150); // wczytuje dane z pliku iris.data do wektora par

    void normalizuj();

    void rozdzielDane(int ileDanychUczenia, int ileDanychTestowych);    // zalecane 30,10 (by zostalo 10 na walidacyjne)
                                                                    // rozdziela dane z daneWszystkie na dane uczenia, testowe oraz walidacyjne i kopiuje do vektorow
                                                                    // suma iledanychUczenia i testowych musi byc <50 bo musi cos zostac na walidacje
                                                                    // 50 bo jakby rozpatrujemy jeden rodzaj kwiatka i chcemy by w kazdym z wektorow jak daneuczenia, danetestowe iwalidacyjne
                                                                    // chcemy by bylo po tyle samo kazdych kwiatkow

    void rozdzielDaneUstalonaKolejnosc();

    vector<double> pobierzWejscieUczenia(int x);
    vector<double> pobierzWyjscieUczenia(int x);

    vector<double> pobierzWejscieTestowania(int x);
    vector<double> pobierzWyjscieTestowania(int x);

    vector<double> pobierzWejscieWalidacyjne(int x);
    vector<double> pobierzWyjscieWalidacyjne(int x);


    void normalizujUczenia();
    void normalizujTestowania();
    void normalizujWalidacyjne();

    void wypiszWektorPar(VEKTORPAR wek);

    //double losuj() { return dist(gen);};
    //double losujInt() {return liczbaNaturalna(gen);};
    void rozdzielanieDlaWykresuZbiorow();
};


#endif //KWIATKI_DANE_H
