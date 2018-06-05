
#include <iostream>
#include <iomanip>

#include "headers/Matematyka.h"
//#include "headers/Losowanie.h"
#include "headers/Dane.h"

#include "headers/Neuron.h"
#include "headers/Gnuplot.h"
#include "headers/StrukturyZestaw.h"
#include "headers/SiecNeuronow.h"

static int ILOSC_EPOK = 20;
static int iloscCentrow = 2;
static double PMIN = 0.75;//0.75;  // minimalny potencjal neuronu wykorzystuje w 'martwych' neuronach/ wartosc z wkladu
double LAMBDA;// zmienia sie co iteracje
const double LambdaMIN = 0.0000005;
const double LambdaMAX = 1.0;
/////////// LAMBDA NIE MOZE BYC < 0
double ETA = 0.5; // wspolczynnik nauki
//vector<double> ETA({1.0, 0.0, 0.0, 0.0, 0.0}); // TODO zobaczyc wartosci  // to jest WSPOLCZYNNIK NAUKI dla kolejnego sąsiada
static int K_iluSasiadomZmieniamy = 1;//ETA.size();   // do gazu neuronowego ile neuronow najblizszych punktowi będzie tez adoptowalo wagi
////////// !!!!!! K_iluSasiadomZmieniamy musi być < iloscCentrow


bool czyPotencjalUwgledniac = false; // czy stopowac wygrywjace ciagle neurony bo ruszyly sie martwe neurony

Zestaw A(-10, 15, -12, 8, "attract_small.txt");
Zestaw B(0, 10000, -10, 15, "attract.txt");
Zestaw C(-10, 15, -12, 8, "plikStaryZLY.txt");

using namespace std;

    ////////////////////// deklaracja danych

    Zestaw zestaw = A;  // z ktorego pliku dane brac
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
            //siec.zapiszDoPliku(siec.zadanePunkty,"maly.txt");
            //rysuj("attract_small");
    ///////////////////  PROGRAM

    for(int i = 0; i < ILOSC_EPOK; ++i) // Cała siec  wersja off-line wyklad str28 //TODO jeszcze zrobic karanie zwyciezcow co za duzo wygrywaja
    {
        ///// zmniejszam lambde
        LAMBDA = LambdaMAX * pow(LambdaMIN / LambdaMAX, (double) i / ILOSC_EPOK);    // wzor z wykladu
        // TODO zrobic zmniejszanie wspolczynnika nauki

        //siec.obliczOdleglosci(siec.zadanePunkty);
        //siec.sortujOdleglosci();
        //siec.adapptacjaWagWersjaOFFLine(czyPotencjalUwgledniac);

        siec.adaptacjaWagGazNeuronowy(czyPotencjalUwgledniac, LAMBDA, ETA, K_iluSasiadomZmieniamy);
//        cout << "WYPIUJE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
//cout <<siec.wypiszOdleglosci();
        if (i < 9)   // na poczatek rysuje wszystkie 9 epok a potem co 10
        {
            siec.sortujOdleglosciDokladnie();
            siec.rysujWykres(iloscCentrow, i, siec.zadanePunkty);
        } else {

            if (i % 10 == 0) {
                siec.sortujOdleglosciDokladnie();
                siec.rysujWykres(iloscCentrow, i, siec.zadanePunkty);
            }
        }

        double blad = siec.obliczBladKwantyzacji();
        cout << "Epoka " << i << ", blad kwantyzacji: " << blad << endl;
        foutKwantyzacji << i << " " << blad << endl;

        if (i > ILOSC_EPOK - 5)
        {
            siec.sortujOdleglosciDokladnie();
            siec.rysujWykres(iloscCentrow, i, siec.zadanePunkty);
            //getchar();
            //getchar();
         }

    }
    // zeby zobaczyc ostatni wyglad
    siec.sortujOdleglosci();
    cout <<endl<<endl;
    //cout <<siec.wypiszOdleglosci();

    siec.rysujWykres(iloscCentrow, ILOSC_EPOK,siec.zadanePunkty);

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