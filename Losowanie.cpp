/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Losowanie.cpp
 * Author: Przemo
 * 
 * Created on 15 kwietnia 2018, 10:16
 */

#include "Losowanie.h"
#include "Losowanie.h"

Losowanie::Losowanie()
    : dist{-0.5, 0.5}
{
    rng.seed(random_device()());
}

float Losowanie::losuj()
{
    return dist(rng);
}

Losowanie& Losowanie::get()
{
    static Losowanie instance;
    return instance;
}

Losowanie::~Losowanie()
{
    //dtor
}