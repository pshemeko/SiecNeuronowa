
#include <iostream>
#include <iomanip>

#include "headers/Matematyka.h"
//#include "headers/Losowanie.h"
#include "headers/Dane.h"

#include "headers/Neuron.h"
#include "headers/Gnuplot.h"
#include "headers/StrukturyZestaw.h"
#include "headers/SiecNeuronow.h"

int ILOSC_EPOK = 200;

int iloscCentrow = 30;
double PMIN = 0.75;  // minimalny potencjal neuronu wykorzystuje w 'martwych' neuronach
bool czyPotencjalUwgledniac = false; // czy stopowac wygrywjace ciagle neurony bo ruszyly sie martwe neurony

Zestaw A(0, 1000, -10, 15, "attract_small.txt");
Zestaw B(0, 10000, -10, 15, "attract_small.txt");
Zestaw C(-10, 15, -12, 8, "plikStaryZLY.txt");

using namespace std;

    ////////////////////// deklaracja danych

    Zestaw zestaw = C;  // z ktorego pliku dane brac
    //double Neuron::wartoscBiasu = 1.0;
    //bool Neuron::czyJestBias = false;


int main() {

    srand(time(NULL));

    /////// deklaracja zmiennych
    string nazwaPlikuBledu = "Wykres_Bledu_Kwantyzacji";
    ofstream foutKwantyzacji(nazwaPlikuBledu+".txt");

    vector<int> wymiar({zestaw.xmin, zestaw.xmax, zestaw.ymin, zestaw.ymax});    // to jest przekazywane do neuronu ktory jest centum

    SiecNeuronow siec(wymiar, iloscCentrow, zestaw, PMIN);
    //siec.zapiszCentra();
    //siec.wczytajCentra();

    ///////////////////  PROGRAM

    for(int i = 0; i < ILOSC_EPOK; ++i) // Cała siec  wersja off-line wyklad str28 //TODO jeszcze zrobic karanie zwyciezcow co za duzo wygrywaja
    {
        //cout << endl << "Epoka :" << i << " \t";

        siec.obliczOdleglosci(siec.zadanePunkty);

        siec.sortujOdleglosci();

        siec.adapptacjaWagWersjaOFFLine(czyPotencjalUwgledniac);

        if(i <2)   // na poczatek rysuje wszystkie 20 epok a potem co 10
        {
            siec.rysujWykres(iloscCentrow, i);
        }
        else
        {
            if(i % 10 == 0) siec.rysujWykres(iloscCentrow, i);
        }

        double blad = siec.obliczBladKwantyzacji();
        cout << "Epoka " << i <<", blad kwantyzacji: " << blad <<endl;
        foutKwantyzacji << i << " " << blad << endl;
    }
    foutKwantyzacji.close(); //musze zamknac plik zanim bede zniego rysowal wykres
    rysuj(nazwaPlikuBledu); // rysuje wykres bledow kwantyzacji

    ////// tworze mozaike
    siec.tworzMozaike();
    siec.obliczOdleglosci(siec.mozaika);
    siec.sortujOdleglosci();

// sprawdzam tylko
    siec.zapiszCetraZPotencjalem();


    cout << endl<<endl <<"\t KONIEC" <<endl;




}