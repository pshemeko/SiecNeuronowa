cmake_minimum_required(VERSION 3.8.2)
project(SiecNeuronowa)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(SiecNeuronowa
        nbproject/private/c_standard_headers_indexer.c
        nbproject/private/cpp_standard_headers_indexer.cpp
        Dane.cpp
        Dane.h
        Losowanie.cpp
        Losowanie.h
        main.cpp
        Neuron.cpp
        Neuron.h
        SiecNeuronow.cpp
        SiecNeuronow.h)
