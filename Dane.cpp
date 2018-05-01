/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dane.cpp
 * Author: Przemo
 * 
 * Created on 19 kwietnia 2018, 18:41
 */

#include "Dane.h"

Dane::Dane(int ileLiczbLosowac)
: dist{0, ileLiczbLosowac}, ileLiczb{ileLiczbLosowac},liczbaNaturalna{0,ileLiczbLosowac} //TODO chyba piwinna by double ileLiczbLosowac
{
    gen.seed(random_device()());
}

//Dane::Dane(const Dane& orig) {
//}

Dane::~Dane() {
}
vector<double> Dane::pobierzWejscie(int x)
{
    /*
    vector<int> wek0 = {1,0,0,0};
    vector<int> wek1 = {0,1,0,0};
    vector<int> wek2 = {0,0,1,0};
    vector<int> wek3 = {0,0,0,1};
    */
    vector<double> wek0 = {1.0,0.0,0.0,0.0};
    vector<double> wek1 = {0.0,1.0,0.0,0.0};
    vector<double> wek2 = {0.0,0.0,1.0,0.0};
    vector<double> wek3 = {0.0,0.0,0.0,1.0};
    switch(x)
    {
        case 0:
            return wek0;
            break;
        case 1:
            return wek1;
            break;
        case 2:
            return wek2;
            break;
        case 3:
            return wek3;
            break;
        default:
            throw "Niepoprawna wartosc nie ma tylu wektorow wejsciowych!!!!!!!!!!!!!!!!!!!!!!!/n\n";
            break;
    }
}

vector<double> Dane::pobierzWyjscie(int x)
{/*
    vector<int> wek0  = {1,0,0,0};
    vector<int> wek1 = {0,1,0,0};
    vector<int> wek2 = {0,0,1,0};
    vector<int> wek3 = {0,0,0,1};
*/
    vector<double> wek0 = {1.0,0.0,0.0,0.0};
    vector<double> wek1 = {0.0,1.0,0.0,0.0};
    vector<double> wek2 = {0.0,0.0,1.0,0.0};
    vector<double> wek3 = {0.0,0.0,0.0,1.0};
    switch(x)
    {
        case 0:
            return wek0;
            break;
        case 1:
            return wek1;
            break;
        case 2:
            return wek2;
            break;
        case 3:
            return wek3;
            break;
        default:
            throw "NIepoprawna wartosc nie ma tylu wektorow WYJjsciowych!!!!!!!!!!!!!!!!!!!!!!!/n\n";
            break;
    }
}

vector<int> Dane::wylosujKolejnoscPobierania()
{
    vector<int> wynik;
    vector<int> wzor;
    for(int i = 0; i < ileLiczb; i++) wzor.push_back(i);
    // teraz losowo wyjmujem elementy z wektora wzor i wkladamy do wynik az wektor bedzie pusty

        for (int i=ileLiczb; i > 1; --i)
        {
            int wylosowana =  liczbaNaturalna(gen) %i;

            wynik.push_back(wzor[wylosowana]);
            wzor.erase(wzor.begin()+wylosowana);
        }

    int wylosowana =  liczbaNaturalna(gen); // zwiekrza losowosc danych okrsl jak pobierac pozostale elementy czy od konca czy nie
        if (wylosowana%2)
        {
            for(auto x: wzor) wynik.push_back(x);
        }
        else{
            for(vector<int>::reverse_iterator it=wzor.rbegin(); it!=wzor.rend(); it++ )
                wynik.push_back(*it);
        }
    return wynik;
}


void Dane::menu()
{
    system("CLS");


    cout << " Co chcesz zrobic?"<< endl<<endl;
    cout << " 1) Tryb nauki?"<< endl;
    cout << " 2) Tryb testowania "<< endl;

}

void Dane::menuTestowanie()
{
    cout <<endl<<endl << "Na której danej chcesz testować wynik?"<< endl<<endl;
    cout << "0. {1, 0, 0, 0}"<<endl;
    cout << "1. {0, 1, 0, 0}"<<endl;
    cout << "2. {0, 0, 1, 0}"<<endl;
    cout << "3. {0, 0, 0, 1}"<<endl;
    cout << "5. Koniec!"<<endl;
}

VEKTORPAR Dane::WczytajPlik(void) // wczytuje dane z pliku iris.data do wektora par
{
    VEKTORPAR wektorPar;
    ifstream plik;
    plik.open("iris.data", ios_base::in);   // otworz plik w trybie do odczytu
    double liczba;
    string nazwa;

    if (!plik.is_open())
    {
        cout << "\nBlad otwarcia pliku\n";
    }

    cin.exceptions(ios_base::failbit);
    try {


    }catch(ios_base::failure &bf)
    {
        cout << bf.what() << endl;
        cout << "O!!! TRAGEDIA\n";
    }
    cin.clear(); // zeruje stan strumienia by mozna bylo dalej wczytywac

plik.clear(); // zerowanie stanu strumienia
}