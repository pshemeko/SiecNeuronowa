//
// Created by Przemo on 2018-06-01.
//

#ifndef KWIATKI_GNUPLOT_H
#define KWIATKI_GNUPLOT_H


#include <iostream>
#include <string>
#include <fstream>

using std::cerr;
using std::string;

class Gnuplot
{
private:
    FILE *pipe;
public:
    Gnuplot();
    ~Gnuplot();
    void operator () (const string &command);


};


static void rysuj(string str)
{
    Gnuplot gnuplot;

    //string a = "0.0";
    //string b = "1.0";

    gnuplot("set term png truecolor\n"); //ustawienie terminala na png
    //gnuplot("set output \"plikStaryZLY.png\" \n");  //ustawienie pliku do którego maj¹ zostaæ zapisane dane
    gnuplot("set output \""+str+".png\" \n");  //ustawienie pliku do którego maj¹ zostaæ zapisane dane
    gnuplot("set xlabel 'Wartosci'\n"); //ustawienie opisu osi x
    gnuplot("set ylabel 'liczebnosc'\n"); // ustawienie osi y
    gnuplot("set boxwidth 0.5 relative\n");
    gnuplot("set style fill transparent solid 0.5 noborder\n");
    gnuplot("set xtics rotate out\n");
    gnuplot("set key title \"Legenda\" box\n");
    //gnuplot("plot 'plikStaryZLY.txt' with points ps 0.3\n");
    gnuplot("plot '"+str+".txt' with points ps 0.3\n");
    //gnuplot("plot 'attract.txt' using 2:xtic(1) ti \"");
    //gnuplot(a);
    //gnuplot("\" w boxes lc rgb'red', 'attract_small.txt' using 2:xtic(1) ti \"");
    //gnuplot(b);
    //gnuplot("\" w boxes lc rgb'green'\n");
    //gnuplot("exit\n");

}

static void rysuj1(string komenda, string nazwaPlikuPNG)
{
    Gnuplot gnuplot;

    gnuplot("set term png truecolor\n"); //ustawienie terminala na png
    gnuplot("set output \""+nazwaPlikuPNG+".png\" \n");  //ustawienie pliku do którego maja zostac zapisane dane
    gnuplot("set xlabel 'Wartosci'\n"); //ustawienie opisu osi x
    gnuplot("set ylabel 'liczebnosc'\n"); // ustawienie osi y
    gnuplot("set boxwidth 0.5 relative\n");
    gnuplot("set style fill transparent solid 0.5 noborder\n");
    gnuplot("set xtics rotate out\n");
    gnuplot("set key title \"Legenda\" box\n");

    gnuplot(komenda);
    gnuplot("exit\n");

}


#endif //KWIATKI_GNUPLOT_H
