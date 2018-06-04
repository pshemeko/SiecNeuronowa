
#include <iostream>
#include <iomanip>

#include "headers/Matematyka.h"
//#include "headers/Losowanie.h"
#include "headers/Dane.h"

#include "headers/Neuron.h"
#include "headers/Gnuplot.h"
#include "headers/StrukturyZestaw.h"
#include "headers/SiecNeuronow.h"

int ILOSC_EPOK = 20;

int iloscCentrow = 10;
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
            siec.rysujWykres(iloscCentrow, i,siec.zadanePunkty);
        }
        else
        {
            if(i % 10 == 0) siec.rysujWykres(iloscCentrow, i, siec.zadanePunkty);
        }

        double blad = siec.obliczBladKwantyzacji();
        cout << "Epoka " << i <<", blad kwantyzacji: " << blad <<endl;
        foutKwantyzacji << i << " " << blad << endl;
    }
    foutKwantyzacji.close(); //musze zamknac plik zanim bede zniego rysowal wykres
  rysuj(nazwaPlikuBledu); // rysuje wykres bledow kwantyzacji

    ////// tworze mozaike
    string mozaik = "mozaikaaa";
    siec.tworzMozaike();
    siec.obliczOdleglosci(siec.mozaika);
    siec.sortujOdleglosci();

   siec.zapiszDoPliku(siec.mozaika,mozaik+".txt");

    string komendaMozaiki = "set term png truecolor\n set output \'" + mozaik + ".png\' \n";
    komendaMozaiki += "set style fill transparent solid 0.5 noborder\n";
    komendaMozaiki += "set key noautotitle;\n";  // nie wyswietla legendy
    ostringstream s1;
    s1 << "set xrange [" << zestaw.xmin << ":" << zestaw.xmax << "]\n" << "set yrange [" << zestaw.ymin<<":" << zestaw.ymax << "]\n";
    komendaMozaiki += s1.str();
    komendaMozaiki += "plot '"+mozaik+".txt'"+" w points pt 7 ps 1\n";

   // rysuj0(komendaMozaiki); // rysuje wszystkie punkty z wektora mozaiki tylko sprawdzam cz sa te punkty

int nnn = 999999;
//siec.zapiszWszystkoWPliku(iloscCentrow,)

    cout <<endl<<"jest..."<<endl;
    siec.rysujWykres(iloscCentrow,nnn, siec.mozaika, s1.str());


// sprawdzam tylko
    //siec.zapiszCetraZPotencjalem();


    cout << endl<<endl <<"\t KONIEC" <<endl;




}