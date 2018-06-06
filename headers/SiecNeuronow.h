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
#include "Matematyka.h"
#include <fstream>



//static bool CZY_BIAS = true;
//static bool CZY_Z_MOMENTEM = true;
//wspóczynniki
//static double ETA = 0.2; // współczynnik nauki(0.6)  0.9
//static double MI = 0.9; // potrzbne gdy licze z momentem (0.1)  0.6

typedef std::vector< Neuron* > VEKTORDANYCH;
typedef std::vector<std::pair< std::vector<double>, std::vector<double> > > VEKTORPAR; // para numer punktu centum, odleglosc, i ilosc par tyle co punktow w pliku

using namespace std;

class SiecNeuronow {

    bool czyPosortowaneOdleglosci; // zapamietuje czy VEKTORPAR odleglosci jest posortowany
    double potencjalMinimum;
    Zestaw zestaw;
    void obliczpotencjaly();
public:
    void sortujOdleglosciDokladnie(); // robi pelne sortowanie vektorapar odleglosci
    void zapiszDoPliku(VEKTORDANYCH &dana, string nazwaPliku);  //zapisuje neuronyCentralne do pliku


    VEKTORDANYCH zadanePunkty;  // punkty z pliku
    VEKTORDANYCH neuronyCentalne;       // neurony ktore sa centalnymi ktore pokkrywaja przestrzen
    VEKTORDANYCH mozaika;   // wszystkie punkty na plaszczyznie
    VEKTORPAR odleglosci;       // zapisane sa pary: first: numer neuronu i second : odleglosc tego neuronu do danego zadanego punktu

    string wypiszZadanePunkty();
    string wypiszNeurony();
    string wypiszOdleglosci();



    SiecNeuronow(vector<int> &wymiar, int iloscCentrow, Zestaw zestawik, double potencjalMinimalny);

    void obliczOdleglosci(VEKTORDANYCH &wektor);
    void sortujOdleglosci();    // sortuje tak pod nr 0(apierwszy) w parze jest neuron centralny ktory jest najblizej zadanego i-tego neurony


    double obliczBladKwantyzacji(); // cos jak blad sieci // TODO zapisywac do pliku i zrobic wykres jak w sprwku 2b



    void adapptacjaWagWersjaOFFLine(bool czyUwzgledniacPotencjal); // jedna z wersji Klasyczny algorytm WTA

    void adaptacjaWagGazNeuronowy(bool czyUwzgledniacPotencjal, double &lambda, double eta, int iluSasiadomZmieniamy);// vector<double> wspolczynnikiNaukiSasiadow); // ONLINE

    void aptacjaWagGazNeuronowyOFFLine(bool czyUwzgledniacPotencjal, double &lambda, double eta, int iluSasiadomZmieniamy);

    void przesunMartweNeurony(double lambda, double eta);

    string zapiszWszystkoWPliku(int iloscCentrow, string nazwaPlikuCentrow, VEKTORDANYCH &dane); // musi byc posortowane

    string rysujWykres(int iloscCentrow, int numer, VEKTORDANYCH &dane, string komendaJest = "a");   // zapisuje do plikow i rysuje wykres

    void rysujBledyKwantyzacji(string nazwaPlikuBledu);

    void tworzMozaike();    // tworzy mozaike zapisuje wszystkie punkty do vektora

    ///////// POTRZEBNE TYLKO DO SPRAWDZANIA DZIALANIA PODCZAS PISANIA POZNIEJ MOZNA SKASOWAC

    void zapiszCentra();    // potrzebne do testowania ustawien by byly takie same wagi poczatkowe
    void wczytajCentra();   // wczytuje centra z pliku zeby zawsze siec startowala z tymi samymi danymi
    void zapiszCetraZPotencjalem(int numer);     //sprawdam potencjal martwych neuronow
    void zapiszCentraZIlosciaZmian(int numer);

};


#endif //KWIATKI_SIECNEURONOW_H
