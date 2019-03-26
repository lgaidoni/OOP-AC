#pragma once

//Normal includes
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

//User defined headers
#include "CircuitObject.h"
#include "UserInputFunctions.h"
#include "Resistor.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Options.h"

//Using the standard namespace
using namespace std;

//Function to create the component library, given options
vector<circuitObject*> createComponentsLibrary(options options);
//Function returns the components vector