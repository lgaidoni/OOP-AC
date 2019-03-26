#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

const int circuitRequest(); //This function will ask the user what circuit they wish to enter next

const int componentRequest();  //This function asks for resistor, capacitor or inductor

const int nodeNumber();  //This function asks how many nodes are connected to this node

const string createLibrary();  //This function asks if the library is to be made

const string saveToLibrary();  //This function asks whether to save the circuit to a component and add to library

const string addAnotherComponent();  //This function asks whether the user wants to add more components

const int optionsRequest();  //This function asks which option the user would like to choose

const int mainProgramRequest();  //This function asks whether the user wants to open the options menu

const string usingWindows7();  //This function asks if the user is using windows 7