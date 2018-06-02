cmake_minimum_required(VERSION 3.8)
project(kwiatki)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        headers/Matematyka.h
        headers/Losowanie.h
        src/Losowanie.cpp
        src/Dane.cpp
        headers/Dane.h
        src/Neuron.cpp
        headers/Neuron.h
        src/SiecNeuronow.cpp
        headers/SiecNeuronow.h
        tests/testLosowanie.cpp src/Gnuplot.cpp headers/Gnuplot.h headers/Testy.h headers/StrukturyZestaw.h)
add_executable(kwiatki ${SOURCE_FILES})