//
// Created by Przemo on 2018-05-16.
//

#include "../headers/SiecNeuronow.h"
#include "../headers/Matematyka.h"

SiecNeuronow::SiecNeuronow(vector<int> iloscNeuronowNaWarstweDomyslna ) // ilosc neuronow na arstwe to wektor ktory zawiera na kazdej pozycji ile neuronow jest w danej warstwie
        : iloscNeuronowNaWarstwe{iloscNeuronowNaWarstweDomyslna}
{
    // tworze warstwe rozprowadzajaca

    vector<Neuron*> rozprowadzajaca ;
    for (int i = 0; i < iloscNeuronowNaWarstwe[0]; ++i )
    {
        rozprowadzajaca.push_back( new Neuron(1,CZY_BIAS));
        rozprowadzajaca[i]-> wagi[0] = 1.0;   // bo warstwa wejsciowa jest tylko do rozprowadzenia sygnalu wiec tam wag nie ma
        rozprowadzajaca[i]-> wagi[1] = 0.0;   //TODO sprawdzic ale chyba w rozprowadzajacej nie ma biasu wiec jego wage zeruje
    }
    siecNeuronow.push_back(rozprowadzajaca);   // dla warstwy wejsciowej

    // tworze siec

    for(int j = 1; j < iloscNeuronowNaWarstwe.size(); ++j) //tworze warstwy ukryte i wyjsciowa
    {
        vector<Neuron*> warstwa ;

        for (int i = 0; i < iloscNeuronowNaWarstwe[j];++i)
        {
            warstwa.push_back(new Neuron(iloscNeuronowNaWarstwe[j-1],CZY_BIAS));
        }
        siecNeuronow.push_back(warstwa);
    }
}

double SiecNeuronow::bladSieci()
{
    int ostWarstwa = iloscNeuronowNaWarstwe.size() - 1;
    double suma = 0.0;

    for(int i = 0; i < iloscNeuronowNaWarstwe[ostWarstwa]; ++i)
    {
        double ile = siecNeuronow[ostWarstwa][i] -> blad;
        suma += 0.5*ile*ile;
    }
    return suma/(double)iloscNeuronowNaWarstwe[ostWarstwa];
}

void SiecNeuronow::obliczanieWyjsciaNeuronow(vector<double> danaWej)
{
    //dla warstwy rozprowadzajacej
    for(int i = 0; i < iloscNeuronowNaWarstwe[0]; i++)
        siecNeuronow[0][i] -> wyjscie = danaWej[i];

    //dla sieci
    for(int i = 1; i < iloscNeuronowNaWarstwe.size(); ++i)
    {
        for(int j=0; j< iloscNeuronowNaWarstwe[i]; ++j)
        {
            double suma = 0.0;  // wyjscie z sumatora
            for(int k = 0; k< iloscNeuronowNaWarstwe[i-1]; ++k)
            {
                suma += siecNeuronow[i][j] -> wagi[k] * siecNeuronow[i-1][k] -> wyjscie;
            }
            // jeszcze bias
            suma += CZY_BIAS * siecNeuronow[i][j] -> wagi[iloscNeuronowNaWarstwe[i-1]] * siecNeuronow[i][j] -> wartoscBiasu;
            siecNeuronow[i][j] -> wyjscie = funkcjaAktywacji(suma);
        }
    }
}

void SiecNeuronow::obliczanieBledow(vector<double> danaWyj)
{
    // dla wyjsciowej
    int ostatnia = iloscNeuronowNaWarstwe.size() -1;
    for(int i = 0; i < iloscNeuronowNaWarstwe[ostatnia]; i++)
    {
        // popchodna jest obliczana na podstawie wartosci funkcji aktywacji neuronu (czyli wyjscia)
        siecNeuronow[ostatnia][i] ->blad = (danaWyj[i] - siecNeuronow[ostatnia][i] -> wyjscie) * pochodnaFunkcjiAktywacji(siecNeuronow[ostatnia][i] -> wyjscie);
    }

    //dla sieci - propagujc wstecz
    for(int i = ostatnia -1; i > 0; --i) // bo dla rozprowadzajacej nie robimy
    {
        for(int j = 0; j < iloscNeuronowNaWarstwe[i]; ++j)
        {
            double suma = 0.0;
            for (int k = 0; k < iloscNeuronowNaWarstwe[i + 1]; ++k) {
                suma += siecNeuronow[i][j]-> wagi[k] * siecNeuronow[i + 1][k] -> blad;
            }
            siecNeuronow[i][j]->blad = suma * pochodnaFunkcjiAktywacji(siecNeuronow[i][j] -> wyjscie);
        }
    }
}

void SiecNeuronow::ZmianaWagSieci()
{

    for(int i = 1; i < iloscNeuronowNaWarstwe.size(); ++i)
    {
        for(int j = 0; j < iloscNeuronowNaWarstwe[i]; ++j)
        {
            for(int k = 0; k < iloscNeuronowNaWarstwe[i-1]; ++k)
            {
                siecNeuronow[i][j] -> wagi[k] += ETA * siecNeuronow[i][j] -> blad * siecNeuronow[i-1][k] -> wyjscie;
                // gdy momentum wzor z danych mlodego
                siecNeuronow[i][j] -> wagi[k] += CZY_Z_MOMENTEM * MI * (ETA * siecNeuronow[i][j] -> blad * siecNeuronow[i-1][k] ->wyjscie);
            }
            // jeszcze wage biasu zmieniam
            int kk = iloscNeuronowNaWarstwe[i-1];
            siecNeuronow[i][j] -> wagi[kk] += ETA * siecNeuronow[i][j] -> blad * siecNeuronow[i][j] -> wartoscBiasu; //TODO CZEMU ETA tu i niżej
            siecNeuronow[i][j] -> wagi[kk] += CZY_Z_MOMENTEM * MI * (ETA * siecNeuronow[i][j] -> blad * siecNeuronow[i][j] ->wartoscBiasu);

        }
    }

}

void SiecNeuronow::wypiszSiebie()
{
    cout <<endl << "TERAZ SIEC WYJSC:"<<endl;
    for(int i = 0; i<siecNeuronow.size(); i++)
    {


        for(int j = 0; j<siecNeuronow[i].size(); j++)
        {


            cout << siecNeuronow[i][j] -> wyjscie << "\t";
        }
        cout <<endl <<"warstwa ukryta: "<< i << endl;
    }

}


void SiecNeuronow::wypiszBledy(){
    cout <<endl << "TERAZ BLEDY"<<endl;
    for(int i = 0; i<siecNeuronow.size(); i++)
    {


        for(int j = 0; j<siecNeuronow[i].size(); j++)
        {


            cout << siecNeuronow[i][j] -> blad << "\t";
        }
        cout <<endl <<"warstwa ukryta: "<< i << endl;
    }

}

void SiecNeuronow::wypiszRaz(vector<double> wyj)
{
    //manipulowanie wyswietlaniem
    ios_base::fmtflags old = cout.setf(ios_base::left, ios_base::adjustfield); // cout.setf( ios_base::showpos); //pokazuje znak + zawsze

    //Wyswietlanie

    cout << endl;
    for (int i = 0; i < iloscNeuronowNaWarstwe[iloscNeuronowNaWarstwe.size() - 1]; i++)
    {
                cout.precision(12);
                cout << i<<"\tWart oczekiwana:" << wyj[i];
                cout << "\tWyjscie: ";
                cout.width(17);
                cout << siecNeuronow[iloscNeuronowNaWarstwe.size() - 1][i]->wyjscie;
                cout << "\tWagi: ";
                for (int j = 0; j < iloscNeuronowNaWarstwe[iloscNeuronowNaWarstwe.size() - 1]; j++) {
                    cout.width(16);
                    cout << siecNeuronow[iloscNeuronowNaWarstwe.size() - 1][i]->wagi[j] << "  ";
                }
                /*
                cout << "\tStareWagi: ";
                for (int j = 0; j < iloscNeuronowNaWarstwe[iloscNeuronowNaWarstwe.size() - 1]; j++) {
                    cout.width(14);
                    cout << siecNeuronow[iloscNeuronowNaWarstwe.size() - 1][i]->stareWagi[j] << "\t";
                }
                 */
                cout << endl;

    }
    cout.setf(old, ios_base::adjustfield);// przywracam stare ustwaienia
}


string SiecNeuronow::testowanieSieci2(vector<double> wejscie, vector<double> wyjscie, int &trafiony) // TODO jest zle bo skopiowane i nie przerobione
{
    obliczanieWyjsciaNeuronow(wejscie);
    obliczanieBledow(wyjscie);

    ostringstream s1;
    string info;
    int ile = iloscNeuronowNaWarstwe.size() - 1;
    int ostatnia = iloscNeuronowNaWarstwe[ile];

    ios_base::fmtflags old = cout.setf(ios_base::fixed, ios_base::adjustfield);

    // szukam maximum
    //vector<double> wyj;
    //for(int i=0; i< ostatnia; i++) wyj.push_back( siecNeuronow[ile][i]-> wyjscie);
    // double maksymalna = *std::max_element(wyj.begin(), wyj.end() ); // TODO albo bez -1

    //szukam maksima
    int wykryty = 1; // ktory kwiatek zostal wykryty ktore wyjscie ma maksymalna wartosc
    int oczekiwany = 0;
    //int dobrzeWykryto = 0, zleWykryto =0;
    double wartosc = siecNeuronow[ile][0]->wyjscie;

    for (int i = 0; i < ostatnia; i++) {
        cout << endl;

        if (siecNeuronow[ile][i]->wyjscie > wartosc) {
            wartosc = siecNeuronow[ile][i]->wyjscie;
            wykryty = i + 1;
        }


        ////
        ostringstream ss;
        ss << "Neuron nr[" << i << "]:";

        cout.width(18);
        cout << ss.str();
        cout << " |";
        cout.width(13);
        cout << wejscie[i] << " |";
        cout.width(8);
        cout << wyjscie[i];
        cout << " |";
        cout.width(20);
        cout.precision(10);
        cout << siecNeuronow[ile][i]->wyjscie;
        cout << " |";
    // do plik
        s1 << ss.str() << " |" <<  wejscie[i] << " |";
        s1 <<  wyjscie[i] <<  " |";
        s1 << siecNeuronow[ile][i]->wyjscie << " |" <<endl;

    }
    cout.setf(old, ios_base::adjustfield);

    //cout << " " << cout.width(9) << minimalna <<"  .." << os.str() << " ,," << endl;
    for (int i = 0; i < wyjscie.size(); ++i)
        if (1.0 == wyjscie[i]) oczekiwany = i + 1;

    cout <<  " Oczekiwany :" << oczekiwany << " Wykryty kwiatek numer: " << wykryty<<endl;
    s1 <<  " Oczekiwany :" << oczekiwany << " Wykryty kwiatek numer: " << wykryty<<endl<<endl;

    info = s1.str();
    if(oczekiwany == wykryty) {
        trafiony += 1;
    }

return info;


}