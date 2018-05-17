//
// Created by Przemo on 2018-05-15.
//

#ifndef KWIATKI_MENU_H
#define KWIATKI_MENU_H

//#include <random>
#include <iostream>
//#include <stdlib.h>
//#include <fstream>

using namespace std;

static void menu()
{
    //system("CLS");
    cout << " Co chcesz zrobic?"<< endl<<endl;
    cout << " 1) Tryb nauki?"<< endl;
    cout << " 2) Tryb testowania "<< endl;
}

static void menuNaglowek()
{

    cout.width(18);
    cout<< "wyliczenia sieci:";
    cout<<" |";
    cout.width(13);
    cout << "Wejscie";
    cout << " |";
    cout.width(8);
    cout << "Ma byc";
    cout << " |";
    cout.width(20);
    cout<< " Wyliczenie sieci";
    cout << " |";
    cout.width(18);
    cout<< "wykryty kwiatek\n";
}

#endif //KWIATKI_MENU_H
