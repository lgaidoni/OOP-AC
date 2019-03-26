#pragma once
//Normal includes
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

//User created headers
#include "CircuitObject.h"
#include "Options.h"

//Using standard namespace
using namespace std;

//This function will draw the empty circuit (just box and components)
void drawEmpty(options options, vector<circuitObject*> components);