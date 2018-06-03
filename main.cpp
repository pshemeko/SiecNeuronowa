
#include <iostream>
#include <iomanip>

#include "headers/Matematyka.h"
//#include "headers/Losowanie.h"
#include "headers/Dane.h"

#include "headers/Neuron.h"
#include "headers/Gnuplot.h"
#include "headers/StrukturyZestaw.h"
#include "headers/SiecNeuronow.h"

int ILOSC_EPOK = 1000;

int iloscCentrow = 5;

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
    vector<int> wymiar({zestaw.xmin, zestaw.xmax, zestaw.ymin, zestaw.ymax});    // to jest przekazywane do neuronu ktory jest centum

    SiecNeuronow siec(wymiar, iloscCentrow, zestaw);

    ///////////////////  PROGRAM

    for(int i = 0; i < 20; ++i) // Cała siec  wersja off-line wyklad str28 //TODO jeszcze zrobic karanie zwyciezcow co za duzo wygrywaja
    {
        cout << endl << "Epoka :" << i << " \t";

        siec.obliczOdleglosci();

        siec.sortujOdleglosci();

        siec.adapptacjaWagWersjaOFFLine();

        siec.rysujWykres(iloscCentrow, i);

    }
cout << endl<<endl <<"\t KONIEC" <<endl;


/*
    //rysuj(zestaw.nazwa);
    vector<int> v({zestaw.xmin, zestaw.xmax, zestaw.ymin, zestaw.ymax});
    vector<int> v1({-5, 5, 11, 21, 0, 1, 2, 10, -10, -5});
    Neuron n1(v);
    Neuron n2(v1);
    for (int i = 0; i < n1.wagi.size(); i++) { cout << n1.wagi[i] << "  "; };
    cout << endl << "drugi" << endl;
    for (int i = 0; i < n2.wagi.size(); i++) { cout << n2.wagi[i] << "  "; };
    Dane dana;
    vector<Neuron *> punkty;
    dana.wczytaj_wzorzec(punkty, zestaw.nazwa);
    int ile = 0;

    for (int i = 0; i < punkty.size(); i++) {
        for (int j = 0; j < punkty[i]->wagi.size(); j++) {
            cout << punkty[i]->wagi[j] << " ";
        }
        cout << endl;
        ile++;
    }

    cout << endl <<endl<< ile;
*/
}