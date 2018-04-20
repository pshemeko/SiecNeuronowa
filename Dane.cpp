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
: dist{0, ileLiczbLosowac}, ileLiczb{ileLiczbLosowac},liczbaNaturalna{0,ileLiczbLosowac}
{
    gen.seed(random_device()());
}

//Dane::Dane(const Dane& orig) {
//}

Dane::~Dane() {
}
vector<int> Dane::pobierzWejscie(int x)
{
    vector<int> wek0 = {1,0,0,0};
    vector<int> wek1 = {0,1,0,0};
    vector<int> wek2 = {0,0,1,0};
    vector<int> wek3 = {0,0,0,1};
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

vector<int> Dane::pobierzWyjscie(int x)
{
    vector<int> wek0  = {1,0,0,0};
    vector<int> wek1 = {0,1,0,0};
    vector<int> wek2 = {0,0,1,0};
    vector<int> wek3 = {0,0,0,1};
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
//for(int i = 0; i< cos; i++)

        for (int i=ileLiczb-1; i > 1; --i)
        {
            int wylosowana =  liczbaNaturalna(gen) %i;

            //int liczba = rand() % 199; //199 liczba pierwsza
            //int kierunek = rand() % 100;
        wynik.push_back(wzor[wylosowana]);
        wzor.erase(wzor.begin()+wylosowana);
        }
    int wylosowana =  liczbaNaturalna(gen);
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