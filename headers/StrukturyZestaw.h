//
// Created by Przemo on 2018-06-02.
//

#ifndef KWIATKI_STRUKTURYZESTAW_H
#define KWIATKI_STRUKTURYZESTAW_H


struct Zestaw
{
    int xmin, xmax; //zakres x
    int ymin, ymax; //zakres y
    char * nazwa;   //nazwa pliku
    Zestaw(int xmi, int xma, int ymi, int yma, string naz)
            : xmin(xmi), xmax(xma), ymin(ymi), ymax(yma)//, nazwa(naz)
    {
        nazwa = new char[naz.length() + 1];
        strcpy(nazwa, naz.c_str());

    }
};

#endif //KWIATKI_STRUKTURYZESTAW_H
