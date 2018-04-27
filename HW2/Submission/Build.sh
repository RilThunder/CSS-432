#!/bin/bash
# My first script

g++ -pthread -std=c++14 -o Server Server.cpp
g++ -std=c++14 -o Retriever Retriever.cpp
g++ -std=c++14 -o BadRetriever BadRetriever.cpp
