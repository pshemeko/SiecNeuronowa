
#include <iostream>

#include "headers/Matematyka.h"
//#include "headers/Losowanie.h"
#include "headers/Dane.h"
#include "headers/Menu.h"
#include "headers/SiecNeuronow.h"


using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    //cout << funkcjaAktywacji(10.0,1.0);

    //Dane dan(50);
    //int x;
    Losowanie l1(-0.5,0.5);
    Losowanie l2(0,50);
    vector<int> wekt(52,0);
    for (int i=0; i<20000; i++)
    {
        wekt[l2.losujInt()] += 1;
        cout <<l1.losujWagi() <<" ";
        if(i%20 ==0) cout <<endl;
        //     x =dan.losujInt();
        //if (x<1) cout << x <<" ";

    }
    for (int i=0; i< wekt.size(); i++)
        cout << i <<": "<<wekt[i] <<endl;

    cout <<"\nTeraz sprawdzam czy dobrze losuje"<<endl;

    Dane dan;
    vector<int> wylosowane = dan.wylosujKolejnoscPobierania(50);
    int suma=0, dodane = 0;
    for(int i =0; i < wylosowane.size(); i++)
    {
        suma += wylosowane[i];
        cout << wylosowane[i] << " ";
    }
    for(int i =0; i<50; i++) dodane +=i;

    cout <<"\n suma = " << suma <<"  Dodane = " <<dodane;

    return 0;
}
