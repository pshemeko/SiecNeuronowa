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
}