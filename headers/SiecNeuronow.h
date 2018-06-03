//
// Created by Przemo on 2018-05-16.
//

#ifndef KWIATKI_SIECNEURONOW_H
#define KWIATKI_SIECNEURONOW_H

//#include <windows.h> // dla funkcji sleep do testu
#include <vector>
#include <iostream>
#include <algorithm>
#include "Neuron.h"
#include "StrukturyZestaw.h"
#include "Dane.h"
#include "Gnuplot.h"
#include <fstream>



//static bool CZY_BIAS = true;
//static bool CZY_Z_MOMENTEM = true;
//wspóczynniki
static double ETA = 0.2; // współczynnik nauki(0.6)  0.9
//static double MI = 0.9; // potrzbne gdy licze z momentem (0.1)  0.6

typedef std::vector< Neuron* > VEKTORDANYCH;
typedef std::vector<std::pair< std::vector<double>, std::vector<double> > > VEKTORPAR; // para numer punktu centum, odleglosc, i ilosc par tyle co punktow w pliku

using namespace std;

class SiecNeuronow {

    void zapiszDoPliku(VEKTORDANYCH dana, string nazwaPliku);  //zapisuje neuronyCentralne do pliku

    VEKTORDANYCH zadanePunkty;  // punkty z pliku
    VEKTORDANYCH neuronyCentalne;       // neurony ktore sa centalnymi ktore pokkrywaja przestrzen
    VEKTORPAR odleglosci;       // zapisane sa pary: first: numer neuronu i second : odleglosc tego neuronu do danego zadanego punktu

    bool czyPosortowaneOdleglosci; // zapamietuje czy VEKTORPAR odleglosci jest posortowany
public:

    string wypiszZadanePunkty();
    string wypiszNeurony();
    string wypiszOdleglosci();



    SiecNeuronow(vector<int> &wymiar, int iloscCentrow, Zestaw zestaw);

    void obliczOdleglosci();
    void sortujOdleglosci();    // sortuje tak pod nr 0(apierwszy) w parze jest neuron centralny ktory jest najblizej zadanego i-tego neurony

    double obliczBladKwantyzacji(); // cos jak blad sieci // TODO zapisywac do pliku i zrobic wykres jak w sprwku 2b

    void adapptacjaWagWersjaOFFLine(); // jedna z wersji


    string zapiszWszystkoWPliku(int iloscCentrow, string nazwaPlikuCentrow); // musi byc posortowane

    string rysujWykres(int iloscCentrow, int numer);   // zapisuje do plikow i rysuje wykres

    void rysujBledyKwantyzacji(string nazwaPlikuBledu);

};


#endif //KWIATKI_SIECNEURONOW_H
