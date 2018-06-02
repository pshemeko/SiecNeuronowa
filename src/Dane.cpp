//
// Created by pobi on 5/14/18.
//

#include "../headers/Dane.h"


Dane::~Dane() {
}

//void Dane::normalizuj()
//{
    /*
    int ileDanych = daneWszystkie[0].first.size();

    for (int i = 0; i < ileDanych; i++) {
        maksima.push_back(daneWszystkie[0].first[i]);
        minima.push_back(daneWszystkie[0].first[i]);
    }

    for(int i = 1; i < daneWszystkie.size(); i++)   //po wszystkich danych wejsciowych
    {
        for(int j = 0; j < ileDanych ; j++) // ile jest danych wejsciowyych w sensie rodzajow pomiarow w kwiatkach sa 4 dane
        {
            if( daneWszystkie[i].first[j] > maksima[j] )  maksima[j] = daneWszystkie[i].first[j];
            if( daneWszystkie[i].first[j] < minima[j] )  minima[j] = daneWszystkie[i].first[j];
        }
    }

    // normalizacja wzorem xij = (xij – colmmin) /(colmmax – colmmin)
    for(int i = 0; i < daneWszystkie.size(); i++)   //po wszystkich danych wejsciowych
    {
        for(int j = 0; j < ileDanych ; j++) // ile jest danych wejsciowyych w sensie rodzajow pomiarow w kwiatkach sa 4 dane
        {
            daneWszystkie[i].first[j] = (daneWszystkie[i].first[j] - minima[j] ) / (maksima[j] - minima[j]);
        }
    }
     */
//}

/*
void Dane::wypiszWektor(VEKTORDANYCH wek)
{

    for(int i = 0; i < wek.size(); i++)   //po wszystkich danych wejsciowych
    {
        cout << i << "\t|";
        for (int j = 0; j < wek[i].first.size(); j++) // ile jest danych wejsciowyych w sensie rodzajow pomiarow w kwiatkach sa 4 dane
        {
            cout << wek[i].first[j] << "\t";
        }
        cout << "\t Wyjscia-second: ";
        for (int j = 0; j < wek[i].second.size(); j++) // ile jest danych wejsciowyych w sensie rodzajow pomiarow w kwiatkach sa 4 dane
        {
            cout << wek[i].second[j] << "\t";
        }

        cout <<endl;
    }
    cout << "koniec par!" << endl;

}
*/

/*
void Dane::wczytajPlik(string nazwaPliku,int ilosclinii) // wczytuje dane z pliku iris.data do wektora par
{

   double raz,dwa,trzy,cztery;
   char c1;
   string nazwa;

   ifstream plik;
   plik.open(nazwaPliku.c_str(), ios_base::in);   // otworz plik w trybie do odczytu
   if (!plik.is_open())
   {
       cout << "\nBlad otwarcia pliku\n";
   }

   while(ilosclinii--) { //cin.peek()!= EOF
       plik >> raz >> c1 >> dwa >> c1 >> trzy >> c1 >> cztery >> c1 >> nazwa;
       //    cout << raz << c1 << dwa << c1 << trzy << c1 << cztery << c1 << nazwa << endl;
       //vector<double> dana1 ({raz, dwa, trzy, cztery});
       vector<double> dana1;
       dana1.push_back(raz);
       dana1.push_back(dwa);
       dana1.push_back(trzy);
       dana1.push_back(cztery);

       vector<double> dana2;

       if(nazwa == "Iris-setosa")     dana2 = vector<double>({1.0, 0.0, 0.0});
       if(nazwa == "Iris-versicolor") dana2 = vector<double>({0.0, 1.0, 0.0});
       if(nazwa == "Iris-virginica")  dana2 = vector<double>({0.0, 0.0, 1.0});
       pair<vector<double>, vector<double>> para = std::make_pair(dana1, dana2);

       daneWszystkie.push_back(para);
   }

}
*/

/*
vector<int> Dane::wylosujKolejnoscPobierania(int ileLiczb)
{
    Losowanie losowana(0,ileLiczb);
    vector<int> wynik;
    vector<int> wzor;
    for(int i = 0; i < ileLiczb; i++) wzor.push_back(i);

    // teraz losowo wyjmujem elementy z wektora wzor i wkladamy do wynik az wektor bedzie pusty
    for (int i=ileLiczb; i > 10; --i)
    {
        int wylosowana =  losowana.losujInt() %i;

        wynik.push_back(wzor[wylosowana]);
        wzor.erase(wzor.begin()+wylosowana);
    }

    int wylosowana =  losowana.losujInt(); // zwiekrza losowosc danych okrsl jak pobierac pozostale elementy czy od konca czy nie
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

 */

void Dane::wczytaj_wzorzec(vector<Neuron * > &wzorzec,char *nazwa){
    fstream dane;
    dane.open(nazwa, ios::in | ios::out) ;
    double liczba;
    int i=0;
    int j=0;
    //wzorzec.push_back(vector<double>());
    vector<double> vv;
    if(dane.is_open()){
        cout<<"plik otwarty.."<<endl;
        while(!dane.eof() ){
            dane>>liczba;
            vv.push_back(liczba);
            j=vv.size();
            // cout<<wzorzec[i][j-1]<<"d";
            if(j==2){
                i++;
                Neuron *nn = new Neuron(vv[0],vv[1]);
                wzorzec.push_back(nn);

                vv.clear();
                //wzorzec.push_back(vector<double>());
                // cout<<endl;
            }
        }
        dane.close();
        //wzorzec.pop_back();
    }
    else cout<<"plik nie zostal otwarty"<<endl;
}
