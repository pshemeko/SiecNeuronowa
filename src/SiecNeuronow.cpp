//
// Created by Przemo on 2018-05-16.
//

#include "../headers/SiecNeuronow.h"
#include "../headers/Matematyka.h"

SiecNeuronow::SiecNeuronow(vector<int> &wymiar, int iloscCentrow, Zestaw zestaw)
{
    for(int i = 0; i < iloscCentrow; ++i)
    {
        neuronyCentalne.push_back(new Neuron(wymiar));
    }
    Dane::wczytaj_wzorzec(zadanePunkty, zestaw.nazwa);
    odleglosci.clear();
    czyPosortowaneOdleglosci = false;
}

string SiecNeuronow::wypiszZadanePunkty()
{
    ostringstream ss;
    for(int i = 0; i < zadanePunkty.size(); i++)
    {
        for(int j = 0; j < zadanePunkty[i]->wagi.size(); ++j)
        {
            ss << zadanePunkty[i]->wagi[j] << " ";
        }
        ss << endl;
    }
    return ss.str();
}

string SiecNeuronow::wypiszNeurony()
{
    ostringstream ss;
    for(int i = 0; i < neuronyCentalne.size(); i++)
    {
        for(int j = 0; j < neuronyCentalne[i]->wagi.size(); ++j)
        {
            ss << neuronyCentalne[i]->wagi[j] << " ";
        }
        ss << endl;
    }
    return ss.str();
}

string SiecNeuronow::wypiszOdleglosci()
{
    ostringstream ss;
    for(int i = 0; i < odleglosci.size(); i++)
    {
        ss<<"Punkt " << i <<": ";
        for(int j = 0; j < odleglosci[i].first.size(); ++j)
        {
            ss <<" punkt " << odleglosci[i].first[j] <<" odl: " <<odleglosci[i].second[j] ;
        }
        ss << endl;
    }
    return ss.str();
}


void SiecNeuronow::obliczOdleglosci()
{
    odleglosci.clear();
    czyPosortowaneOdleglosci = false;
    //odleglosci.push_back(make_pair(vector<double>(),vector<double>()));
    for(int i = 0 ; i < zadanePunkty.size(); ++i)
    {
        vector<double> punkt;
        vector<double> odlegly;
        for(int j = 0; j < neuronyCentalne.size(); ++j)
        {
            double odl = neuronyCentalne[j]->odlegloscEuklidesowa(zadanePunkty[i]);
            punkt.push_back(j);
            odlegly.push_back(odl);
        }
        odleglosci.push_back(make_pair(punkt,odlegly));
    }
}

void SiecNeuronow::sortujOdleglosci()   // po 0 sa najmniejsze odleglosci
{

    for(int i = 0; i < odleglosci.size(); ++i)
    {
        for(int j = 1; j < odleglosci[i].first.size(); ++j)
        {
            if( odleglosci[i].second[0] > odleglosci[i].second[j])
            {
                // zamieniamy
                swap(odleglosci[i].first[0], odleglosci[i].first[j]);
                swap(odleglosci[i].second[0], odleglosci[i].second[j]);

            }
        }
    }
    czyPosortowaneOdleglosci = true;
}

double SiecNeuronow::obliczBladKwantyzacji() // TODO zrobic na wykladzie jest i do wykresow dac
{
    // musi byc posortowane
    if(!czyPosortowaneOdleglosci) sortujOdleglosci();

    double blad = 0.0;

    // obliczam z wzoru z wykladow na E
    for(int i = 0; i < odleglosci.size(); ++i )
    {
        //double odl = neuronyCentalne[odleglosci[i].first[0]]->odlegloscEuklidesowa(zadanePunkty[i]); // mozna prosciejponizej
        double odl = odleglosci[i].second[0];// bo second to odleglosc
        odl *=odl; //bo kwadrat we wzorze
        blad += odl;
    }
    blad /= odleglosci.size();
    return blad;
}

void SiecNeuronow::adapptacjaWagWersjaOFFLine()
{
    //obliczOdleglosci();
    //sortujOdleglosci();
    int ile = 0;

    vector<double> wspolrzedneNowe = neuronyCentalne[0]->wagi;  // aby mial ten sam rozmiar

    for(int i = 0; i < wspolrzedneNowe.size(); ++i) wspolrzedneNowe[i] = 0.0; // zerowanie

    // alggorytm adaptacji parametrow funkcji radialnych  procesie samoorganizacji str. 28.
    for(int i = 0; i < neuronyCentalne.size(); ++i)
    {
        for(int j = 0; j < odleglosci.size(); ++j)
        {
            if(odleglosci[j].first[0] == i)
            {
                for(int l = 0; l < wspolrzedneNowe.size(); ++l) // sumuje kazda wspolrzedna
                {
                    wspolrzedneNowe[l] +=zadanePunkty[j]->wagi[l];
                }
                ile++;
            }
        }
        if(ile !=0)
        {
            for(int k = 0; k < wspolrzedneNowe.size(); ++k)
            {
                wspolrzedneNowe[k] = wspolrzedneNowe[k] / ile;
                neuronyCentalne[i]->wagi[k] = wspolrzedneNowe[k];
            }
        }
        ile = 0;
        for(int i = 0; i < wspolrzedneNowe.size(); ++i) wspolrzedneNowe[i] = 0.0; // zerowanie
    }

}

void SiecNeuronow::zapiszDoPliku(VEKTORDANYCH dana, string nazwaPliku)
{
    ofstream zapis(nazwaPliku);//obiekt tworzymy tylko raz

    for(int i=0; i<dana.size(); i++){
        for(int j=0;j<dana[i]->wagi.size();j++){
            zapis<<dana[i]->wagi[j]<<" ";
        }
        zapis<<endl;
    }

    zapis.close();
}

string SiecNeuronow::zapiszWszystkoWPliku(int iloscCentrow,string nazwaPlikuCentrow)
{
    string zwracany;
    zapiszDoPliku(neuronyCentalne, nazwaPlikuCentrow);   // zapisuje neurony centralne do pliku by moc rysowac je

    // musi byc posortowane
    if(!czyPosortowaneOdleglosci) sortujOdleglosci();

    string nazwa;

    //int l=0;
    //int a=1;
    VEKTORDANYCH p1;

    for(int i=0;i<iloscCentrow;i++)
    {
        sprintf((char*)nazwa.c_str(), "%d", i);
        string nazwa1 = nazwa.c_str();
        nazwa1=nazwa1+".txt";
                //char *nazwa3 = new char[nazwa1.length() + 1];
                //strcpy(nazwa3, nazwa1.c_str());
  zwracany += nazwa1 +" ";
        for(int j=0;j<odleglosci.size();j++)
        {
            if(odleglosci[j].first[0] == i)
            {
                p1.push_back(new Neuron(zadanePunkty[j]->wagi[0], zadanePunkty[j]->wagi[1]));
                //p1.push_back(vector<double>());
                //p1[l].push_back(wzorzec[j][0]);
                //p1[l].push_back(wzorzec[j][1]);
                //l++;

            }
            // cout<<nazwa<<" ";
        }
        zapiszDoPliku(p1,nazwa1);
        p1.clear();
        //l=0;
    }
    p1.clear();

    return zwracany;
}


string SiecNeuronow::rysujWykres( int iloscCentrow, int numer)
{
    //char *plikCentrow = "neuronyCentralne.txt";
    string nazwaPlikuCentrow = "neuronyCentralne.txt";
    string zwracany;

    zwracany = zapiszWszystkoWPliku(iloscCentrow, nazwaPlikuCentrow);

    string nazwa1;
    string s0="plot ";
    string s1=" w points ps 0.5 pt 7 ";
    ostringstream ss;
    string nn;

    for(int i = 0 ; i < iloscCentrow; ++i)  // tworze pliki oraz komnde do plota
    {
        sprintf((char*)nazwa1.c_str(), "%d", i);
        string nazwa2 = nazwa1.c_str();
        nazwa1=nazwa2+".txt";
        s0=s0+"'"+nazwa1+"'"+s1+", ";
    }

    s0=s0+ "'"+nazwaPlikuCentrow + "' \n";// " w points ps 2 pt 1 lc rgb 'red' \n";

    ss << numer;
    nn = ss.str();

    zwracany = "\n" + s0 + "\n";
 //cout << endl << s0 <<endl;
    rysuj1(s0,nn);
    //rysuj(nazwa2);
    //getchar() ;
return zwracany;
}

