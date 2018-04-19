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

Dane::Dane() {
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
