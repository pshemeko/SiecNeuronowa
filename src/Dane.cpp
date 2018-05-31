//
// Created by pobi on 5/14/18.
//

#include "../headers/Dane.h"
/*
Dane::Dane(int ileLiczbLosowac)
        : ileLiczb{ileLiczbLosowac} //,dist{0, ileLiczbLosowac}, liczbaNaturalna{0, ileLiczbLosowac} //TODO chyba piwinna by double ileLiczbLosowac
{
   // gen.seed(random_device()());
}
 */


Dane::~Dane() {
}

vector<double> Dane::pobierzWejscieUczenia(int x)
{
    return daneUczenia[x].first;
}

vector<double> Dane::pobierzWyjscieUczenia(int x)
{
    return daneUczenia[x].second;
}

vector<double> Dane::pobierzWejscieTestowania(int x)
{
    return daneTestowe[x].first;
}

vector<double> Dane::pobierzWyjscieTestowania(int x)
{
    return daneTestowe[x].second;
}

vector<double> Dane::pobierzWejscieWalidacyjne(int x)
{
    return daneWalidacyjne[x].first;
}

vector<double> Dane::pobierzWyjscieWalidacyjne(int x)
{
    return daneWalidacyjne[x].second;
}

void Dane::normalizuj()
{
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
}

/*
void Dane::normalizujUczenia()
{
    int ileDanych = daneUczenia[0].first.size();
    vector<double> maksima;
    vector<double> minima;

    for (int i = 0; i < ileDanych; i++) {
        maksima.push_back(daneUczenia[0].first[i]);
        minima.push_back(daneUczenia[0].first[i]);
    }

    for(int i = 1; i < daneUczenia.size(); i++)   //po wszystkich danych wejsciowych
    {
        for(int j = 0; j < ileDanych ; j++) // ile jest danych wejsciowyych w sensie rodzajow pomiarow w kwiatkach sa 4 dane
        {
            if( daneUczenia[i].first[j] > maksima[j] )  maksima[j] = daneUczenia[i].first[j];
            if( daneUczenia[i].first[j] < minima[j] )  minima[j] = daneUczenia[i].first[j];
        }
    }

    // normalizacja wzorem xij = (xij – colmmin) /(colmmax – colmmin)
    for(int i = 0; i < daneUczenia.size(); i++)   //po wszystkich danych wejsciowych
    {
        for(int j = 0; j < ileDanych ; j++) // ile jest danych wejsciowyych w sensie rodzajow pomiarow w kwiatkach sa 4 dane
        {
            daneUczenia[i].first[j] = (daneUczenia[i].first[j] - minima[j] ) / (maksima[j] - minima[j]);
        }
    }
}
*/

void Dane::wypiszWektorPar(VEKTORPAR wek)
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


void Dane::rozdzielDane(int ileDanychUczenia, int ileDanychTestowych)
{
    //Losowanie losowana(0,50);
    // pierwszy kwiatek rodzielam
    {
        vector<int> kolejnosc = wylosujKolejnoscPobierania(50); // kolejnosc pierszego kwiatka
        int i = 0;
        for (; i < ileDanychUczenia; i++) {
            daneUczenia.push_back(daneWszystkie[kolejnosc[i]]);
        }
        for (int j = 0; j < ileDanychTestowych; j++) {
            daneTestowe.push_back((daneWszystkie[kolejnosc[i]]));
            i++;
        }
        for (; i < kolejnosc.size(); i++)
            daneWalidacyjne.push_back(daneWszystkie[kolejnosc[i]]);
    }

    // drugi kwiatek rodzielam
    {
        vector<int> kolejnosc = wylosujKolejnoscPobierania(50); // kolejnosc pierszego kwiatka
        int i = 0;
        for (; i < ileDanychUczenia; i++) {
            daneUczenia.push_back(daneWszystkie[50 + kolejnosc[i]]);
        }
        for (int j = 0; j < ileDanychTestowych; j++) {
            daneTestowe.push_back((daneWszystkie[50 + kolejnosc[i]]));
            i++;
        }
        for (; i < kolejnosc.size(); i++)
            daneWalidacyjne.push_back(daneWszystkie[50 + kolejnosc[i]]);
    }

    // trzeci kwiatek rodzielam
    {
        vector<int> kolejnosc = wylosujKolejnoscPobierania(50); // kolejnosc pierszego kwiatka
        int i = 0;
        for (; i < ileDanychUczenia; i++) {
            daneUczenia.push_back(daneWszystkie[100 + kolejnosc[i]]);
        }
        for (int j = 0; j < ileDanychTestowych; j++) {
            daneTestowe.push_back((daneWszystkie[100 + kolejnosc[i]]));
            i++;
        }
        for (; i < kolejnosc.size(); i++)
            daneWalidacyjne.push_back(daneWszystkie[100 + kolejnosc[i]]);
    }
}

void Dane::rozdzielDaneUstalonaKolejnosc()
{
    int i = 0;
    for (; i < 30; i++) {
        daneUczenia.push_back(daneWszystkie[i]);
    }
    for (int j = 0; j < 10; j++) {
        daneTestowe.push_back(daneWszystkie[i]);
        i++;
    }
    for (; i < 50; i++)
    {
        daneWalidacyjne.push_back(daneWszystkie[i]);

    }
    // drugi kwiatek
    for (; i < 50+30; i++) {
        daneUczenia.push_back(daneWszystkie[i]);
    }
    for (int j = 0; j < 10; j++) {
        daneTestowe.push_back(daneWszystkie[i]);
        i++;
    }
    for (; i < 50+50; i++)
    {
        daneWalidacyjne.push_back(daneWszystkie[i]);

    }
    // trzeci kwiatek
    for (; i < 100+30; i++) {
        daneUczenia.push_back(daneWszystkie[i]);
    }
    for (int j = 0; j < 10; j++) {
        daneTestowe.push_back(daneWszystkie[i]);
        i++;
    }
    for (; i < daneWszystkie.size(); i++)   // wszystkie do konca juz
    {
        daneWalidacyjne.push_back(daneWszystkie[i]);

    }
}

void Dane::rozdzielDaneUstalonaKolejnoscOdKonca()
{
    int i = 0;
    for (; i < 10; i++) {
        daneWalidacyjne.push_back(daneWszystkie[i]);
    }
    for (int j = 0; j < 10; j++) {
        daneTestowe.push_back(daneWszystkie[i]);
        i++;
    }
    for (; i < 50; i++)
    {
        daneUczenia.push_back(daneWszystkie[i]);

    }
    // drugi kwiatek
    for (; i < 50+10; i++) {
        daneWalidacyjne.push_back(daneWszystkie[i]);
    }
    for (int j = 0; j < 10; j++) {
        daneTestowe.push_back(daneWszystkie[i]);
        i++;
    }
    for (; i < 50+50; i++)
    {
        daneUczenia.push_back(daneWszystkie[i]);

    }
    // trzeci kwiatek
    for (; i < 100+10; i++) {
        daneWalidacyjne.push_back(daneWszystkie[i]);
    }
    for (int j = 0; j < 10; j++) {
        daneTestowe.push_back(daneWszystkie[i]);
        i++;
    }
    for (; i < daneWszystkie.size(); i++)   // wszystkie do konca juz
    {
        daneUczenia.push_back(daneWszystkie[i]);

    }
}


void Dane::rozdzielanieDlaWykresuZbiorow() // wczytuje dane z pliku iris.data do wektora par
{

    double raz, dwa, trzy, cztery;
    char c1;
    string nazwa;

    string nazwaPliku = "iris.data";
    int ilosclinii = 50;

    // dwie pierwsze dane tu zapisze
    ofstream plik1s;
    plik1s.open("Iris-setosa1.txt"); // dwie pierwsze wartosci na 1szy wykres
    if (!plik1s.is_open()) {
        cout << "\nBlad otwarcia pliku\n";
    }
    ofstream plik1ve;
    plik1ve.open("Iris-versicolor1.txt"); // dwie pierwsze wartosci na 1szy wykres
    if (!plik1ve.is_open()) {
        cout << "\nBlad otwarcia pliku\n";
    }
    ofstream plik1vi;
    plik1vi.open("Iris-virginica1.txt"); // dwie pierwsze wartosci na 1szy wykres
    if (!plik1vi.is_open()) {
        cout << "\nBlad otwarcia pliku\n";
    }

    // dwie drugie dane tu zapisze
    ofstream plik2s;
    plik2s.open("Iris-setosa2.txt"); // dwie pierwsze wartosci na 1szy wykres
    if (!plik2s.is_open()) {
        cout << "\nBlad otwarcia pliku\n";
    }
    ofstream plik2ve;
    plik2ve.open("Iris-versicolor2.txt"); // dwie pierwsze wartosci na 1szy wykres
    if (!plik2ve.is_open()) {
        cout << "\nBlad otwarcia pliku\n";
    }
    ofstream plik2vi;
    plik2vi.open("Iris-virginica2.txt"); // dwie pierwsze wartosci na 1szy wykres
    if (!plik2vi.is_open()) {
        cout << "\nBlad otwarcia pliku\n";
    }


    ifstream plik;
    plik.open(nazwaPliku.c_str(), ios_base::in);   // otworz plik w trybie do odczytu
    if (!plik.is_open()) {
        cout << "\nBlad otwarcia pliku\n";
    }

    while (ilosclinii--) { //cin.peek()!= EOF
        plik >> raz >> c1 >> dwa >> c1 >> trzy >> c1 >> cztery >> c1 >> nazwa;
        //    cout << raz << c1 << dwa << c1 << trzy << c1 << cztery << c1 << nazwa << endl;
        //vector<double> dana1 ({raz, dwa, trzy, cztery});

        plik1s << raz << " " << dwa << endl;
        plik2s << trzy << " " << cztery << endl;
    }

    ilosclinii = 50;
    while (ilosclinii--) { //cin.peek()!= EOF
        plik >> raz >> c1 >> dwa >> c1 >> trzy >> c1 >> cztery >> c1 >> nazwa;
        //    cout << raz << c1 << dwa << c1 << trzy << c1 << cztery << c1 << nazwa << endl;
        //vector<double> dana1 ({raz, dwa, trzy, cztery});

        plik1ve << raz << " " << dwa << endl;
        plik2ve << trzy << " " << cztery << endl;
    }

    ilosclinii = 50;
    while (ilosclinii--) { //cin.peek()!= EOF
        plik >> raz >> c1 >> dwa >> c1 >> trzy >> c1 >> cztery >> c1 >> nazwa;
        //    cout << raz << c1 << dwa << c1 << trzy << c1 << cztery << c1 << nazwa << endl;
        //vector<double> dana1 ({raz, dwa, trzy, cztery});

        plik1vi << raz << " " << dwa << endl;
        plik2vi << trzy << " " << cztery << endl;
    }

    plik1s.close();
    plik2s.close();
    plik1ve.close();
    plik1ve.close();
    plik1vi.close();
    plik1vi.close();
}